file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)
target_sources(${PROJECT_NAME} PUBLIC ${SRCS} ${HDRS})
