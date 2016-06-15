set(popcontrol_test_srcs pop_control_test.cpp  test_all.cpp)

add_executable(popcontroltest ${popcontrol_test_srcs})
target_link_libraries(popcontroltest popcontrolhao)
target_link_libraries(popcontroltest ${lib_all})

install(TARGETS popcontroltest DESTINATION test)
