DB_NAME=gotochatdatabase
DB_USER=gotochat
DB_USER_PASS=gotochat
su postgres <<EOF
createdb  $DB_NAME;
psql -c "CREATE USER $DB_USER WITH PASSWORD '$DB_USER_PASS';"
psql -c "grant all privileges on database $DB_NAME to $DB_USER;"

psql -U postgres -d  $DB_NAME -c "create table if not exists users ( 
	us_id			SERIAL PRIMARY KEY,
	us_name			varchar(45) NOT NULL,
	us_phone		varchar(13) NOT NULL UNIQUE,
	us_password		varchar(45) NOT NULL
);"

psql -U postgres -d  $DB_NAME -c "create table if not exists chats ( 
	ch_id			SERIAL PRIMARY KEY,
	ch_name			varchar(45) NOT NULL
);"

psql -U postgres -d  $DB_NAME -c "create table if not exists users_chats ( 
	us_id			int NOT NULL REFERENCES users(us_id) ON DELETE CASCADE,
	ch_id			int NOT NULL REFERENCES chats(ch_id) ON DELETE CASCADE,
	CONSTRAINT user_chats_pkey PRIMARY KEY(us_id, ch_id)
);"

psql -U postgres -d  $DB_NAME -c "create table if not exists messages ( 
	ms_id			SERIAL PRIMARY KEY,
	ms_sendTime		timestamp NOT NULL,
	us_id			int REFERENCES users(us_id) ON DELETE SET NULL,
	ch_id			int NOT NULL REFERENCES chats(ch_id) ON DELETE CASCADE
);"

psql -U postgres -d  $DB_NAME -c "create table if not exists textinputs ( 
	tip_id			SERIAL PRIMARY KEY,
	tip_content		varchar(45)
);"

psql -U postgres -d  $DB_NAME -c "create table if not exists voiceinputs ( 
	vip_id			SERIAL PRIMARY KEY,
	vip_content		varchar(45)
);"

psql -U postgres -d  $DB_NAME -c "create table if not exists inputs ( 
	ip_id			SERIAL PRIMARY KEY,
	ip_type			int NOT NULL,
	ms_id			int NOT NULL REFERENCES messages(ms_id) ON DELETE CASCADE,
	tip_id			int REFERENCES textinputs(tip_id) ON DELETE CASCADE,
	vip_id			int REFERENCES voiceinputs(vip_id) ON DELETE CASCADE
);"
echo "Postgres User '$DB_USER' and database '$DB_NAME' created."
EOF