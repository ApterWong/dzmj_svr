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
	ready: 	 "ready":true|false
	tuoguan: "tuoguan":true|false
	chupai:  "chupai":"_cd_"
	hu:		 "hu" : "_cd_"
	gang	 "gang" : "_cd_"
	zgang:   "zgang": "_cd_"
	agang:	 "agang": "_cd_"
	peng	 "peng" : "_cd_"
	chi		 "chi"  : "_abc_"
	cancel	 "cancel":""
	
	timeout: "timeout":"[chupai|hgpc]","roomid":"_roomid_", "tmout_id":\d+
```

> gw --> worker
```
	{"action":3, "user_id":"_UID_", "session":"_session_",
	"cmd":"_cmd_", "":""}
```

> worker --> gw
```
	{"cli_data":{"type":"game", "cmd":"_cmd_", "_cmd-response_":"", "status":"ok", "msg":"_msg_", "what":"???"
	 }, "user_id":["_uid_",...]}
```
response cmd=
```
--	ready:	 "ready":"ready"|"unready"
|	players: "zhuangid":1, "users_info":[{"id(1-4)":1, "user_id":"_uid_", "user_name":"_name_", "score":"_score_"} *4]
|	/*gamestart: "色字":"dd" -- d 十进制数 1-6*/
|	zhuapai_saizi: 数字*2
|	dingwan_saizi: 数字*2
		-1-													-2-
|	gameinit(otherData):  "1":{data}, "2":{data}...  |  "room":{roomdata}
|	gameinit(userData):   "fangwei":"(1-4)", "data":{data}
|	fapai:	   "id":1, "card": int
|	chupai:    "id":1, "card":"_cd_"
|	hint:      "id":1, "hu":{"cards":[a,b,c], "倍数":[1,2,5]}, "gang":"cd", "peng":"cd", "chi":{"card":"cd", "list":
				["abc", "stu"]}
|	chi:       "id":1, "chi":"abc"
|	peng:	   "id":1, "peng":"cd"
|	gang:	   "id":1, "gang":"cd"
|	zgang:	   "id":1, "zgang":"cd"
|	agang:	   "id":1, "agang":""
--	hu:	   	   "id":1, "hu":"cd", "倍数":88, "1":{data}, "2":{data}...
```
----
##### redis 存储
	等待队列key:   readylist
	roomid(uint64_t):		1+, 每局完后, 定时30s, 房间解散(实际玩家可见时间20s, 不准备或未能开局则全部解散, 选择换桌则再次进入ready队列), 
	
##### test Worker
* 准备(cli --> gw)
```
{"action":3, "user_id":"100001", "session":"FD8D8D464C124B60971A66C6D1D7BCC7","cmd":"ready", "ready":true}

{"action":3, "user_id":"100002", "session":"A4F57CB5FD214EA5BBBBF6F36E85D22D","cmd":"ready", "ready":true}

{"action":3, "user_id":"100003", "session":"CAFF6B276168490F827444F62E7490A4","cmd":"ready", "ready":true}

{"action":3, "user_id":"100004", "session":"E3CE08FF98874F5EADD731B6401079D7","cmd":"ready", "ready":true}
```
* gw --> worker
```
{"cli_data":{"action":3, "user_id":"100001", "session":"FD8D8D464C124B60971A66C6D1D7BCC7","cmd":"ready", "ready":"true"}}

{"cli_data":{"action":3, "user_id":"100002", "session":"A4F57CB5FD214EA5BBBBF6F36E85D22D","cmd":"ready", "ready":"true"},"bev":"_bev_"}

{"cli_data":{"action":3, "user_id":"100003", "session":"CAFF6B276168490F827444F62E7490A4","cmd":"ready", "ready":"true"},"bev":"_bev_"}

{"cli_data":{"action":3, "user_id":"100004", "session":"E3CE08FF98874F5EADD731B6401079D7","cmd":"ready", "ready":"true"},"bev":"_bev_"}
```













