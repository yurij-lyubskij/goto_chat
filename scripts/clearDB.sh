#clear all tables with everything in it
DB_NAME=gotochatdatabase
su postgres <<EOF
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE users CASCADE;"
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE chats CASCADE;"
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE users_chats CASCADE;"
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE messages CASCADE;"
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE textinputs CASCADE;"
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE voiceinputs CASCADE;"
psql -U postgres  -d $DB_NAME -c "TRUNCATE TABLE inputs CASCADE;"
echo "Database '$DB_NAME' is above."
EOF