set(src_lib popcontrolhao)

file(GLOB srcs "*.cpp")

add_library(${src_lib} STATIC ${srcs})

install(TARGETS ${src_lib}  DESTINATION lib)
