
TARGTE=libgts.jar
GROUPID=com.libgts.JNI
ARTIFACT=libgts
VERSION=1.0

MVN_FLAGS=-Dmaven.wagon.http.ssl.insecure=true -Dmaven.wagon.http.ssl.allowall=true -Dmaven.wagon.http.ssl.ignore.validity.dates=true

all:
	javac -d . JNI.java
	javah -jni com.libgts.JNI
	jar -cvf $(TARGTE) com/libgts
	mvn install:install-file -Dfile=$(TARGTE) -DgroupId=$(GROUPID) -DartifactId=$(ARTIFACT) -Dversion=$(VERSION) -Dpackaging=jar -DgeneratePom=true $(MVN_FLAGS)