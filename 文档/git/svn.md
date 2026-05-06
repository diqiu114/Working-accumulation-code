## svn基本操作

按标准工作流整理，均在终端执行（路径省略时默认作用于当前工作副本）：

**📥 同步**

- `svn checkout <URL> [路径]`：首次拉取
- `svn checkout <URL> [路径] --username 用户名 --password 密码`：首次拉取
- `svn update`：更新至服务端最新版本

**👀 状态与差异**

- `svn status`：查看变更（`M`修改, `A`新增, `D`删除, `?`未管控, `C`冲突, `!`缺失）
- `svn diff`：查看本地未提交的具体代码差异
- `svn info`：查看当前目录的仓库URL、版本、修订号

**📝 文件管理**

- `svn add <文件/目录>`：纳入版本控制
- `svn delete <文件>`：标记删除（同步删除物理文件）
- `svn revert <文件>`：撤销本地未提交的修改/操作

**📤 提交与追溯**

- `svn commit -m "说明"`：提交本地变更
  - `svn log [-l 20]`：查看提交历史（`-l`限制条数）

- `svn log -r 100:105`：查看指定版本区间

**⚠️ 冲突与清理**

- `svn resolve --accept working <文件>`：手动解决冲突后标记完成
- `svn cleanup`：修复因中断/断电导致的 `Working copy locked` 状态
- `rm -rf ~/.subversion/auth/`：清除缓存的认证信息

💡 **提示**：命令均支持 `--username` `--password` 参数免交互；批量操作可通配符匹配（如 `svn add *.py`）。



## svn配合sftpgo

1. 设置将sftpgo文件夹设置为svn的文件夹

2. sftpgo设置隐藏.svn文件夹内容和对.svn拒绝更改权限

   ![image-20260418155300721](svn.assets/image-20260418155300721.png)

3. 创建脚本文件

   ```
   sudo nano /usr/local/bin/svn_sync.py
   ```

4. 写入代码

   ```
   #!/usr/bin/env python3
   import os, logging, fcntl, subprocess, glob, configparser
   from datetime import datetime, timedelta
   from urllib.parse import unquote
   
   WORK_DIR = os.path.expanduser("~/Desktop/sftpgo-storage")
   LOG_DIR = os.path.expanduser("~/Desktop/sftpgo-storage/svn服务器资料/svn-sync-log")
   LOCK_FILE = "/tmp/svn-sync.lock"
   
   def load_auth(conf_path):
       auth = {}
       config = configparser.ConfigParser()
       config.read(conf_path, encoding='utf-8')
       
       for section in config.sections():
           auth[section] = {
               "username": config.get(section, "username", fallback=""),
               "password": config.get(section, "password", fallback="")
           }
       return auth
   
   def get_log_file():
       """获取当天的日志文件路径"""
       date_str = datetime.now().strftime("%y%m%d")
       log_filename = f"svn-sync-{date_str}.log"
       return os.path.join(LOG_DIR, log_filename)
   
   def cleanup_old_logs(retention_days=30):
       """清理超过保留期的日志文件"""
       if not os.path.exists(LOG_DIR):
           return
       
       cutoff_date = datetime.now() - timedelta(days=retention_days)
       pattern = os.path.join(LOG_DIR, "svn-sync-*.log")
       
       for log_file in glob.glob(pattern):
           try:
               # 从文件名提取日期
               filename = os.path.basename(log_file)
               date_str = filename.replace("svn-sync-", "").replace(".log", "")
               file_date = datetime.strptime(date_str, "%y%m%d")
               
               # 如果文件日期早于截止日期，删除
               if file_date < cutoff_date:
                   os.remove(log_file)
                   print(f"已删除过期日志: {filename}")
           except (ValueError, OSError) as e:
               print(f"处理日志文件时出错: {e}")
   
   def setup_logging():
       """设置日志系统"""
       # 确保日志目录存在
       os.makedirs(LOG_DIR, exist_ok=True)
       
       # 获取当天的日志文件
       log_file = get_log_file()
       
       # 清理过期日志
       cleanup_old_logs(30)
       
       # 配置日志
       logger = logging.getLogger()
       logger.setLevel(logging.INFO)
       
       # 移除已有的handler（避免重复）
       for handler in logger.handlers[:]:
           logger.removeHandler(handler)
       
       # 创建文件handler
       file_handler = logging.FileHandler(log_file, encoding='utf-8')
       file_handler.setLevel(logging.INFO)
       formatter = logging.Formatter("%(asctime)s [%(levelname)s] %(message)s")
       file_handler.setFormatter(formatter)
       logger.addHandler(file_handler)
       
       return logger
   
   # 初始化日志系统
   setup_logging()
   
   # 加载认证信息
   AUTH = load_auth(os.path.expanduser("~/Desktop/svn_auth.conf"))
   
   
   def decode_if_needed(text):
       """智能检测并解码URL编码的文本
       
       如果文本包含URL编码序列（如%XX），则进行解码
       否则返回原文本
       """
       if not text or not isinstance(text, str):
           return text
       
       # 检测是否包含URL编码模式（%后跟两个十六进制字符）
       import re
       if re.search(r'%[0-9A-Fa-f]{2}', text):
           try:
               decoded = unquote(text)
               # 只有当解码后的内容与原内容不同时才使用解码结果
               if decoded != text:
                   logging.debug(f"URL解码: {text} -> {decoded}")
                   return decoded
           except Exception as e:
               logging.warning(f"URL解码失败: {text}, 错误: {e}")
       
       return text
   
   def run_svn(args, cwd, check=True):
       cmd = ["svn", "--non-interactive", "--trust-server-cert"] + args
       res = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
       if res.stdout:
           logging.debug(f"[{cwd}] {res.stdout.strip()}")
       if res.stderr:
           # 智能解码错误信息中的URL编码
           stderr_decoded = decode_if_needed(res.stderr.strip())
           logging.warning(f"[{cwd}] {stderr_decoded}")
       if check and res.returncode != 0:
           # 智能解码错误信息
           stderr_decoded = decode_if_needed(res.stderr.strip())
           raise RuntimeError(f"[{cwd}] SVN失败: {stderr_decoded}")
       return res
   
   def find_svn_dirs(base, max_depth=5):
       """查找所有包含 .svn 的目录（限制最大递归深度）"""
       svn_dirs = []
   
       base = os.path.abspath(base)
       base_depth = base.rstrip(os.sep).count(os.sep)
   
       for root, dirs, files in os.walk(base):
           current_depth = root.rstrip(os.sep).count(os.sep) - base_depth
   
           # 超过最大深度，停止向下递归
           if current_depth >= max_depth:
               dirs[:] = []
               continue
   
           if ".svn" in dirs:
               svn_dirs.append(root)
               dirs[:] = []  # 找到仓库就不再深入
   
       return svn_dirs
   
   def process_repo(repo_path):
       repo_name = os.path.basename(repo_path)
       username = AUTH[repo_name]["username"]
       password = AUTH[repo_name]["password"]
       logging.info(f"📂 处理仓库: {repo_name} ")
   
       # ========== 第一步：先检查本地是否有未提交的变更 ==========
       local_added, local_modified, local_deleted = [], [], []
       
       status_res = run_svn(["status", "--no-ignore"], cwd=repo_path)
       lines = [l.strip() for l in status_res.stdout.splitlines() if l.strip()]
   
       for line in lines:
           if len(line) < 2:
               continue
   
           st, path = line[0], line[2:].strip()
   
           if st in ("?", "A"):
               run_svn(["add", path], cwd=repo_path, check=False)
               local_added.append(path)
           elif st == "!":
               run_svn(["delete", path], cwd=repo_path, check=False)
               local_deleted.append(path)
           elif st in ("M", "~", "C", "R"):
               local_modified.append(path)
           elif st == "D":
               local_deleted.append(path)
   
       # 如果本地有变更，先提交本地变更
       if local_added or local_modified or local_deleted:
           def fmt_list(lst, limit=3):
               if not lst:
                   return ""
               if len(lst) <= limit:
                   return ", ".join(lst)
               return ", ".join(lst[:limit]) + f" ...等{len(lst)}个"
   
           parts = []
           if local_added:    parts.append(f"【添加】{fmt_list(local_added)}")
           if local_modified: parts.append(f"【修改】{fmt_list(local_modified)}")
           if local_deleted:  parts.append(f"【删除】{fmt_list(local_deleted)}")
   
           msg = " ".join(parts) + f" @ {datetime.now():%m-%d %H:%M}"
           if len(msg) > 200:
               msg = msg[:197] + "..."
   
           run_svn([
               "commit", "-m", msg,
               "--username", username,
               "--password", password
           ], cwd=repo_path)
   
           logging.info(f"[{repo_name}] ✅ 本地变更已提交: {msg}")
   
       # ========== 第二步：拉取服务器的更新 ==========
       logging.info(f"[{repo_name}] 开始拉取服务器更新...")
       update_res = run_svn(["update", "--username", username, "--password", password], cwd=repo_path)
       
       # 解析 update 输出，检测从服务器拉取的变更
       server_updated, server_added, server_deleted = [], [], []
       
       for line in update_res.stdout.splitlines():
           line = line.strip()
           if not line:
               continue
           
           # SVN update 输出的格式：状态码 + 空格 + 文件路径
           if len(line) < 2:
               continue
               
           status_code = line[0]
           file_path = line[2:].strip() if len(line) > 2 else ""
           
           if not file_path:
               continue
           
           if status_code == 'U':
               # 更新的文件
               server_updated.append(file_path)
           elif status_code == 'A':
               # 新增的文件
               server_added.append(file_path)
           elif status_code == 'D':
               # 删除的文件
               server_deleted.append(file_path)
           elif status_code == 'G':
               # 合并的文件
               server_updated.append(file_path)
           elif status_code == 'C':
               # 冲突的文件
               server_updated.append(file_path)
       
       # 如果有从服务器拉取的更新，记录日志
       if server_updated or server_added or server_deleted:
           def fmt_list(lst, limit=5):
               if not lst:
                   return ""
               if len(lst) <= limit:
                   return ", ".join(lst)
               return ", ".join(lst[:limit]) + f" ...等{len(lst)}个"
   
           parts = []
           if server_added:   parts.append(f"【服务器新增】{fmt_list(server_added)}")
           if server_updated: parts.append(f"【服务器更新】{fmt_list(server_updated)}")
           if server_deleted: parts.append(f"【服务器删除】{fmt_list(server_deleted)}")
   
           msg = " ".join(parts) + f" @ {datetime.now():%m-%d %H:%M}"
           if len(msg) > 200:
               msg = msg[:197] + "..."
   
           logging.info(f"[{repo_name}] 📥 服务器更新: {msg}")
       else:
           logging.info(f"[{repo_name}] ⏸ 无变更")
   
   def main():
       with open(LOCK_FILE, "w") as lock:
           try:
               fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
           except IOError:
               logging.info("实例已运行，跳过")
               return
   
           try:
               svn_dirs = find_svn_dirs(WORK_DIR)
   
               if not svn_dirs:
                   logging.warning("⚠ 未找到任何 SVN 工作副本")
                   return
   
               logging.info(f"🔍 共发现 {len(svn_dirs)} 个 SVN 目录")
   
               for repo in svn_dirs:
                   try:
                       process_repo(repo)
                   except Exception as e:
                       logging.error(f"[{repo}] ❌ 处理失败: {e}")
   
           finally:
               fcntl.flock(lock, fcntl.LOCK_UN)
   
   if __name__ == "__main__":
       main()
   
   ```

5. 添加执行权限

   ```
   sudo chmod +x /usr/local/bin/svn_sync.py
   ```

6. 设置每5分钟同步一次

   ```
   (crontab -l 2>/dev/null | grep -v "svn_sync.py"; echo "*/5 * * * * /usr/local/bin/svn_sync.py") | crontab -
   ```

如果要通过修改脚本，可以先把脚本移入用户再用vscode改，此时可以保存

```
sudo chown orangepi5pro:orangepi5pro /usr/local/bin/svn_sync.py
sudo chown orangepi5pro:orangepi5pro /usr/local/bin/svn_sync.py
```

