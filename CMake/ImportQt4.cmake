MESSAGE(STATUS "Importing Qt...")

IF(OTB_WRAP_QT)
  FIND_PACKAGE(Qt4 REQUIRED)
  MARK_AS_ADVANCED(QT_QMAKE_EXECUTABLE)
  SET(QT_USE_QTXML 1)
  INCLUDE(${QT_USE_FILE})
ENDIF(OTB_WRAP_QT)
