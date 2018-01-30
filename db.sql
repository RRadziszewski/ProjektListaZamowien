drop database if exists listorder;
create database listorder CHARACTER SET utf8 COLLATE utf8_general_ci;

use listorder;

create table Account(
	UID			int 		AUTO_INCREMENT
	,Name		varchar(24)
	,Surname	varchar(32)
	,Login		varchar(32)
	,Password	varchar(64)
	,Access		int
	,primary key (UID)
);

create table Auction(
	AID			int 		AUTO_INCREMENT
	,UID		int 	
	,Title		text
	,Synopsis	text
	,StartDate	varchar(12)
	,EndDate	varchar(12)
	,UIDA		int
	,primary key (AID)
	,foreign key (UID) references Account(UID)
	,foreign key (UIDA) references Account(UID)
);

insert into Account values ('','Robert','Radziszewski','robcio','12345678',2);
