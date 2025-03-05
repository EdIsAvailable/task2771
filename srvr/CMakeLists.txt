cmake_minimum_required(VERSION 3.10.0)
project(chat2771 VERSION 0.1.0 LANGUAGES C CXX)

find_library(MYSQLCPP_LIB mysqlcppconn REQUIRED)
add_executable(chat2771 Acc.cpp Chat.cpp Logger.cpp Main.cpp Message.cpp NewUser.cpp Server.cpp Socket.cpp UserRepository.cpp db.cpp)


target_link_libraries(chat2771 ${MYSQLCPP_LIB})

include(CTest)
enable_testing()

