CREATE DATABASE gotochatdatabase; 

\c gotochatdatabase

create table if not exists users ( 
	us_id			SERIAL PRIMARY KEY,
	us_name			varchar(45) NOT NULL,
	us_phone		varchar(13) NOT NULL UNIQUE,
	us_password		varchar(45) NOT NULL
);


create table if not exists chats ( 
	ch_id			SERIAL PRIMARY KEY,
	ch_name			varchar(45) NOT NULL
);

create table if not exists users_chats ( 
	us_id			int NOT NULL REFERENCES users(us_id) ON DELETE CASCADE,
	ch_id			int NOT NULL REFERENCES chats(ch_id) ON DELETE CASCADE,
	CONSTRAINT user_chats_pkey PRIMARY KEY(us_id, ch_id)
);

create table if not exists messages ( 
	ms_id			SERIAL PRIMARY KEY,
	ms_sendTime		timestamp NOT NULL,
	us_id			int REFERENCES users(us_id) ON DELETE SET NULL,
	ch_id			int NOT NULL REFERENCES chats(ch_id) ON DELETE CASCADE
);

create table if not exists textinputs ( 
	tip_id			SERIAL PRIMARY KEY,
	tip_content		varchar(45)
);

create table if not exists voiceinputs ( 
	vip_id			SERIAL PRIMARY KEY,
	vip_content		varchar(45)
);

create table if not exists inputs ( 
	ip_id			SERIAL PRIMARY KEY,
	ip_type			int NOT NULL,
	ms_id			int NOT NULL REFERENCES messages(ms_id) ON DELETE CASCADE,
	tip_id			int REFERENCES textinputs(tip_id) ON DELETE CASCADE,
	vip_id			int REFERENCES voiceinputs(vip_id) ON DELETE CASCADE
);