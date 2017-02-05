	定时器服务器,
-------------------
> 数据格式:
```
{"roomid":"_id_", "type":\d+, "count",\d+}
```
* @type:
	* 1:timeout
	* 2: hgpc选择超时
* @count: 回合. 游戏开局为0, 每定时一次回合数+1, 回合数保存在roomdata中
