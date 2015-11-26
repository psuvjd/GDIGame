# GDIGame
GDI游戏开发
***
GDI游戏开发  
	`build(1, n, 1);`  
	`int l = 2, r = n;`  
	`for(int i = 0; i < 30; i++) {`  
		`int m = (l + r) >> 1;`  
		`if (cal(m)) l = m;`  
		`else r = m - 1;`  
	`}`
