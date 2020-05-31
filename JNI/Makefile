
TARGTE=libgts.jar
GROUPID=com.libgts.JNI
ARTIFACT=libgts
VERSION=1.0

MVN_FLAGS=-Dmaven.wagon.http.ssl.insecure=true -Dmaven.wagon.http.ssl.allowall=true -Dmaven.wagon.http.ssl.ignore.validity.dates=true

.PHONY: all headers jars install

all: headers jars install

headers:
	javac -d . JNI.java
	javah -jni com.libgts.JNI
	
jars:
	jar -cvf $(TARGTE) com/libgts
	
install: jars
	mvn install:install-file -Dfile=$(TARGTE) -DgroupId=$(GROUPID) -DartifactId=$(ARTIFACT) -Dversion=$(VERSION) -Dpackaging=jar -DgeneratePom=true $(MVN_FLAGS)