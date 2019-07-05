add_library( MagMatch SHARED
  nodeClass.cpp
  fastDtw.cpp
  magMatchBase.cpp
  dataRead.cpp
  mktMM.cpp
)

target_link_libraries( MagMatch
    ${THIRD_PARTY_LIBS}
)