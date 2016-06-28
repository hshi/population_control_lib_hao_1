set(test_exe popcontroltest)

file(GLOB test_srcs "*.cpp")

add_executable(${test_exe} ${test_srcs})

target_link_libraries(${test_exe} popcontrolhao)

target_link_libraries(${test_exe} ${lib_all})

install(TARGETS ${test_exe}  DESTINATION test)
