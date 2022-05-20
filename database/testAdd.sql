
INSERT INTO users_chats VALUES(1, 1);

INSERT INTO users(us_name, us_phone) VALUES('TestUser', '9657852675');

INSERT INTO chats(ch_name) VALUES('TestChat');

INSERT INTO users_chats VALUES(1, 1);

INSERT INTO messages(ms_sendTime, us_id, ch_id) VALUES('1/1/2020 00:00:00', 1, 1);
INSERT INTO messages(ms_sendTime, us_id, ch_id) VALUES('1/1/2020 00:01:00', 1, 1);

INSERT INTO textinputs(tip_content) VALUES('TestMessage');

INSERT INTO voiceinputs(vip_content) VALUES('/test/voice/path');

INSERT INTO inputs(ip_type, ms_id, tip_id) VALUES(1, 1, 1);

INSERT INTO inputs(ip_type, ms_id, vip_id) VALUES(1, 2, 1);

SELECT * from users;
SELECT * from chats;
SELECT * from users_chats;
SELECT * from messages;
SELECT * from textinputs;
SELECT * from voiceinputs;
SELECT * from inputs;

