drop table if exists users;
drop table if exists chats;
drop table if exists messages;
drop table if exists inputs;

create table if not exists users ( 
userId			serial primary key not null,
userName		varchar(45) not null,
phone			varchar(13) not null
);


create table if not exists users ( 
chatId			serial primary key not null,
chatName		varchar(45) not null,
);

create table if not exists users_chats ( 
chatId			int,
userId			int
);

create table if not exists messages ( 
messageId		serial primary key not null,
sendTime		DATETIME not null,
userId			int references users(userId),
chatId			int references chats(chatId)
);

create table if not exists inputs ( 
inputId			serial primary key not null,
inputType		int not null,
messageId		int references messages(messageId),
textId			int,
textContent		varchar(45),
voiceId			int,
voiceAdress		varchar(45)
);