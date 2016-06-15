set(popcontrol_srcs double_pop_type.cpp  pop_aux.cpp  pop_configuration.cpp)

add_library(popcontrolhao STATIC ${popcontrol_srcs})

install(TARGETS popcontrolhao  DESTINATION lib)
