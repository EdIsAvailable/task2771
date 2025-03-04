SRC = Main.cpp Acc.cpp UserRepository.cpp NewUser.cpp Message.cpp Chat.cpp Server.cpp Socket.cpp db.cpp
TARGET = chats
PREFIX = /home/server/ref2571/srvr
HEADERS = /usr/include/mysql/
LIBS_DIR = /usr/lib/x86_64-linux-gnu

# Правило для сборки исполняемого файла
$(TARGET): $(SRC)
	@g++ -o $@ $^ -I$(HEADERS) -L$(LIBS_DIR) -lmysqlcppconn -ldl -lresolv -lm -lrt

# Правило для очистки
clean:
	@rm -rf *.o *.a $(TARGET)

# Правило для установки
install:
	@install $(TARGET) $(PREFIX)

# Правило для удаления
uninstall:
	@rm -rf $(PREFIX)/$(TARGET)

.PHONY: clean install uninstall
