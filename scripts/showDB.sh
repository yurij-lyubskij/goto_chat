#shows all tables with everything in it (only for tests, might has too big output)
DB_NAME=gotochatdatabase
su postgres <<EOF
psql -U postgres  -d $DB_NAME -c "SELECT * FROM users;"
psql -U postgres  -d $DB_NAME -c "SELECT * FROM chats;"
psql -U postgres  -d $DB_NAME -c "SELECT * FROM users_chats;"
psql -U postgres  -d $DB_NAME -c "SELECT * FROM messages;"
psql -U postgres  -d $DB_NAME -c "SELECT * FROM textinputs;"
psql -U postgres  -d $DB_NAME -c "SELECT * FROM voiceinputs;"
psql -U postgres  -d $DB_NAME -c "SELECT * FROM inputs;"
echo "Database '$DB_NAME' is above."
EOF