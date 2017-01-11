### worker model
##### 准备, 取消准备
> cli --> gw
```json
	{"action":3, "user_id":"_UID_", "session":"_session_",
	"cmd":"_cmd_", "_cmd_":"xxx"}
-> cli
	{"type":"game", "cmd":"_cmd_", "status":"ok", "msg":"...", "what":"???",
	 "_cmd-response_":""}
```
* requests ~cmd=
``` 
	ready: unready:
	tuoguan: "tuoguan":"true"
	chupai:  "card":"_cd_"
	hu:		 "hu" : "_cd_"
	gang	 "gang" : "_cd_"
	zgang:   "zgang": "_cd_"
	agang:	 "agang": "_cd_"
	peng	 "peng" : "_cd_"
	chi		 "chi"  : "_abc_"
	cancel	 "cancel":""
	
```

> gw --> worker
```
	{"cli_data":{"action":3, "user_id":"_UID_", "session":"_session_",
	"cmd":"_cmd_", "":""}, "user_id":"_uid_"}
```

> worker --> gw
```
	{"cli_data":{"type":"game", "cmd":"_cmd_", "_cmd-response_":"", "status":"ok", "msg":"_msg_", "what":"???"
	 }, "user_id":"_uid_"}
```
response cmd=
```
	players: "zhuangid":1, "id(1-4)":{"user_id":"_uid_", "user_name":"_name_", "score":"_score_"} *4
	gamestart: "色字":"dd" -- d 十进制数 1-6
	gameinit:  "1":{data}, "2":{data}...
	fapai:	   "id":1, "card":"_cd_"
	chupai:    "id":1, "card":"_cd_"
	hint:      "id":1, "hu":{"cards":[a,b,c], "倍数":[1,2,5]}, "gang":"cd", "peng":"cd", "chi":{"card":"cd", "list":
				["abc", "stu"]}
	chi:       "id":1, "chi":"abc"
	peng:	   "id":1, "peng":"cd"
	gang:	   "id":1, "gang":"cd"
	zgang:	   "id":1, "zgang":"cd"
	agang:	   "id":1, "agang":""
	hu:	   	   "id":1, "hu":"cd", "倍数":88, "1":{data}, "2":{data}...
```
