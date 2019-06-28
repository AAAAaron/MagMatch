add_library( MagMatch SHARED
  # step.cpp
  # ahrsangle.cpp
  # ahrsrobust.cpp
  # btwfilter.cpp
  # ahrsqsmffilter.cpp
  # ahrsqsmfbfilter.cpp
  # phonerotateangle.cpp
  # gyro.cpp
  # pdrsim.cpp
  # displayattitude.cpp
  # config.cpp
  # attitudeobserver.cpp
  # ktransfcoordinate.cpp
  nodeClass.cpp
  fastDtw.cpp
)

target_link_libraries( MagMatch
    ${THIRD_PARTY_LIBS}
)