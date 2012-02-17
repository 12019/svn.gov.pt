#!/bin/bash

# este ficheiro cria o ficheiro java para correr a bateria de testes apontar para a nova versão do SDK do MW


# Create New File, replacing class name
sed "s/OfficialSDK/NewVersionSDK/g" OfficialSDK.java > NewVersionSDK.java 
# replace Version tested
sed -i "s/version=\"OFFICIAL\"/version=\"NEW-VERSION\"/g" NewVersionSDK.java
#replace imports
sed -i "s/import pteidlib.\*;/import pt.gov.cartaodecidadao.\*;/g" NewVersionSDK.java
# replace SDK class name: pteid->pteidlibJava_Wrapper
sed -i "s/pteid./pteidlibJava_Wrapper./g" NewVersionSDK.java



##########################################################  TO BE FIXED
##  DIFFERET NAMES BETWEEN METHODS - Need to be fixed:
sed -i "s/\.Init(/\.PTEID_Init(/g" NewVersionSDK.java
##  DIFFERET NAMES BETWEEN METHODS - Need to be fixed:
sed -i "s/\.Exit(/\.PTEID_Exit(/g" NewVersionSDK.java
##  DIFFERET NAMES BETWEEN METHODS - Need to be fixed:
sed -i "s/\.GetCardType(/\.PTEID_GetCardType(/g" NewVersionSDK.java





## PTEIDException doesnt exist on new version of MW
sed -i "s/(PteidException e)/(Exception e)/g" NewVersionSDK.java




#FIX - WRONG REPLACE:
sed -i "s/import pteidlibJava_Wrapper.ib.PteidException;/import pteidlib.PteidException;/g" NewVersionSDK.java
