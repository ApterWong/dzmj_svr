### login model
##### login
> cli --> gw
```
{"action":1, "user_name":"admin", "user_pwd":"root"}
```

> gw --> login_svr:
```
v:  {"cli_data":{"action":1, "user_name":"admin", "user_pwd":"root"}, "bev":"_bevstring_", "uni_key":"uni_key"}
x:  {"cli_data":{"action":1, "user_name":"xxx", "user_pwd":"ooo"}, "bev":"_bevstring_", "uni_key":"uni_key"}
x:  {"cli_data":{"action":1, "user_name":12, "user_pwd":34}, "bev":"_bevstring_", "uni_key":"uni_key"}
x:  {"cli_data":{"action":1, "user_name":"", "user_pwd":"00988"}, "bev":"_bevstring_", "uni_key":"uni_key"}
x:  {"action":1, "user_name":"", "user_pwd":"00988"}
```
```
v:  {"cli_data":{"action":2, "user_id":"100000", "session":"CA00D42915D24113B7D3D4E202FFC4F5"}, "bev":""}
x:  {"cli_data":{"action":2, "user_id":"_uid_", "session":"_session_"}, "bev":"_bevstring_"}
```

> gw <-- login_svr
{"cli_data":{"user_id": "id string", "session":"xxx-xxx", "status":"ok", "action":1}, "bev":"bevstring", "uni_key":"uni_key"}


##### cahce_svr
* 登录: 
```
{"action":"login", "user_id":"_id_", "session":"_session_"}
```
	-> 
* 登出: 
```
{"action":"logout", "user_id","_id_", "session":"_session_"}
```
	-> 
修改游戏状态(在线, 离线, 游戏中, 准备):{"action":"modify", "status":"???"};
