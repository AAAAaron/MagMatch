# add_executable( pdrv pdrv.cpp )
# target_link_libraries( pdrv SHS )
# 
add_executable( tets main.cpp )
target_link_libraries( tets MagMatch )
# 
# add_executable( disAtt dis_att.cpp )
# target_link_libraries( disAtt SHS )
# 
# add_executable( testp test_attitude.cpp )
# target_link_libraries( testp SHS )
# 
# add_executable( triangulation triangulation.cpp )
# target_link_libraries( triangulation ${OpenCV_LIBS} )


# add_executable(tstraf test_tranfc.cpp)
# target_link_libraries(tstraf SHS)