create table  photobatch(
	execID integer PRIMARY KEY autoincrement,
	scanDir varchar(1023),	
	scanTime timestamp,
	fileCount integer,
	totalSize integer,
	keepPriority integer default 100,--越大越保留，小就删除
	removeCount integer
);

CREATE TABLE photofile(
	fileID integer PRIMARY KEY autoincrement,
	execID integer,
	--带扩展名
	filename VARCHAR(8191),
	createTime integer,
	modifyTime integer,
	fileSize integer,
	duplicate integer,
	remove integer ,
	sha256 VARCHAR(64)
);

INSERT INTO
	photofile (filename, sha256)
VALUES
	("test");

select
	*
from
	photofile;