# 函数和文件头部信息

    "fileheader.configObj": {
        "createFileTime": true,
        "language": {
            "languagetest": {
                "head": "/$$",
                "middle": " $ @",
                "end": " $/",
                "functionSymbol": {
                    "head": "/** ",
                    "middle": " * @",
                    "end": " */"
                },
                "functionParams": "js"
            }
        },
        "autoAdd": true,
        "autoAddLine": 100,
        "autoAlready": true,
        "annotationStr": {
            "head": "/*",
            "middle": " * @",
            "end": " */",
            "use": false
        },
        "headInsertLine": {
            "php": 2,
            "sh": 2
        },
        "beforeAnnotation": {
            "文件后缀": "该文件后缀的头部注释之前添加某些内容"
        },
        "afterAnnotation": {
            "文件后缀": "该文件后缀的头部注释之后添加某些内容"
        },
        "specialOptions": {
            "特殊字段": "自定义比如LastEditTime/LastEditors"
        },
        "switch": {
            "newlineAddAnnotation": true
        },
        "supportAutoLanguage": [],
        "prohibitAutoAdd": [
            "json"
        ],
        "folderBlacklist": [
            "node_modules",
            "文件夹禁止自动添加头部注释"
        ],
        "prohibitItemAutoAdd": [
            "项目的全称, 整个项目禁止自动添加头部注释, 可以使用快捷键添加"
        ],
        "moveCursor": true,
        "dateFormat": "YYYY-MM-DD HH:mm:ss",
        "atSymbol": [
            "@",
            "@"
        ],
        "atSymbolObj": {
            "文件后缀": [
                "头部注释@符号",
                "函数注释@符号"
            ]
        },
        "colon": [
            ": ",
            ": "
        ],
        "colonObj": {
            "文件后缀": [
                "头部注释冒号",
                "函数注释冒号"
            ]
        },
        "filePathColon": "路径分隔符替换",
        "showErrorMessage": false,
        "writeLog": false,
        "wideSame": false,
        "wideNum": 13,
        "functionWideNum": 0,
        "CheckFileChange": false,
        "createHeader": false,
        "useWorker": false,
        "designAddHead": false,
        "headDesignName": "random",
        "headDesign": false,
        "cursorModeInternalAll": {},
        "openFunctionParamsCheck": true,
        "functionParamsShape": [
            "{",
            "}"
        ],
        "functionBlankSpaceAll": {},
        "functionTypeSymbol": "*",
        "typeParamOrder": "type param",
        "customHasHeadEnd": {},
        "throttleTime": 60000,
        "functionParamAddStr": "",
        "NoMatchParams": "no show param"
    },
    // 头部注释
    "fileheader.customMade": {
        // Author字段是文件的创建者 可以在specialOptions中更改特殊属性
        // 公司项目和个人项目可以配置不同的用户名与邮箱 搜索: gitconfig includeIf  比如: https://ayase.moe/2021/03/09/customized-git-config/
        // 自动提取当前git config中的: 用户名、邮箱
        "Author": "ZhiQiang", // 同时获取用户名与邮箱
        // "Author": "git config user.name", // 仅获取用户名
        // "Author": "git config user.email", // 仅获取邮箱
        // "Author": "OBKoro1", // 写死的固定值 不从git config中获取
        "Date": "Do not edit", // 文件创建时间(不变)
        // LastEditors、LastEditTime、FilePath将会自动更新 如果觉得时间更新的太频繁可以使用throttleTime(默认为1分钟)配置更改更新时间。
        "LastEditors": "ZhiQiang", // 文件最后编辑者 与Author字段一致
        // 由于编辑文件就会变更最后编辑时间，多人协作中合并的时候会导致merge
        // 可以将时间颗粒度改为周、或者月，这样冲突就减少很多。搜索变更时间格式: dateFormat
        "LastEditTime": "Do not edit", // 文件最后编辑时间
        // 输出相对路径，类似: /文件夹名称/src/index.js
        "FilePath": "Do not edit", // 文件在项目中的相对路径 自动更新
        // 插件会自动将光标移动到Description选项中 方便输入 Description字段可以在specialOptions更改
        "Description": "", // 介绍文件的作用、文件的入参、出参。
        // custom_string_obkoro1~custom_string_obkoro100都可以输出自定义信息
    },
    // 函数注释
    "fileheader.cursorMode": {
        "brief": "", // 函数注释生成之后，光标移动到这里
        "param": "", // param 开启函数参数自动提取 需要将光标放在函数行或者函数上方的空白行
        "return": "",
    },
    