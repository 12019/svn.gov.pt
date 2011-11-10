#!/bin/bash

rm -rf pteid-pkg 
mkdir pteid-pkg

mkdir -p pteid-pkg/lib
mkdir -p pteid-pkg/bin
mkdir -p pteid-pkg/eidgui


cp -r lib/*  		pteid-pkg/lib/
cp -r bin/*  		pteid-pkg/bin/
cp -r eidgui/*.qm	pteid-pkg/eidgui/



echo "#!/bin/bash" > pteid-pkg/install_pteid.sh
echo "install -m 755 -p \"lib/libpteidcommon.so.3.5.5\" \"/usr/local/lib/libpteidcommon.so.3.5.5\"" >> pteid-pkg/install_pteid.sh
echo "ln -f -s /usr/local/lib/libpteidcommon.so.3.5.5 /usr/local/lib/libpteidcommon.so"  >> pteid-pkg/install_pteid.sh
echo "ln -f -s /usr/local/lib/libpteidcommon.so.3.5.5 /usr/local/lib/libpteidcommon.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -f -s /usr/local/lib/libpteidcommon.so.3.5.5 /usr/local/lib/libpteidcommon.so.3.5"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libpteiddialogsQT.so.3.5.5\" \"/usr/local/lib/libpteiddialogsQT.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteiddialogsQT.so.3.5.5 /usr/local/lib/libpteiddialogsQT.so"  >> pteid-pkg/install_pteid.sh  
echo "ln -s -f /usr/local/lib/libpteiddialogsQT.so.3.5.5 /usr/local/lib/libpteiddialogsQT.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteiddialogsQT.so.3.5.5 /usr/local/lib/libpteiddialogsQT.so.3.5"  >> pteid-pkg/install_pteid.sh


echo "install -m 755 -p \"bin/pteiddialogsQTsrv\" \"/usr/local/bin/pteiddialogsQTsrv\""  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libpteidcardlayer.so.3.5.5\" \"/usr/local/lib/libpteidcardlayer.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidcardlayer.so.3.5.5 /usr/local/lib/libpteidcardlayer.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidcardlayer.so.3.5.5 /usr/local/lib/libpteidcardlayer.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidcardlayer.so.3.5.5 /usr/local/lib/libpteidcardlayer.so.3.5"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libcardpluginPteid.so.3.0.1\" \"/usr/local/lib/libcardpluginPteid.so.3.0.1\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libcardpluginPteid.so.3.0.1 /usr/local/lib/libcardpluginPteid.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libcardpluginPteid.so.3.0.1 /usr/local/lib/libcardpluginPteid.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libcardpluginPteid.so.3.0.1 /usr/local/lib/libcardpluginPteid.so.3.0"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libcardpluginFull__ACS__.so.3.5.5\" \"/usr/local/lib/libcardpluginFull__ACS__.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libcardpluginFull__ACS__.so.3.5.5 /usr/local/lib/libcardpluginFull__ACS__.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libcardpluginFull__ACS__.so.3.5.5 /usr/local/lib/libcardpluginFull__ACS__.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libcardpluginFull__ACS__.so.3.5.5 /usr/local/lib/libcardpluginFull__ACS__.so.3.5"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libsiscardplugin1__ACS__.so.3.5.5\" \"/usr/local/lib/libsiscardplugin1__ACS__.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libsiscardplugin1__ACS__.so.3.5.5 /usr/local/lib/libsiscardplugin1__ACS__.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libsiscardplugin1__ACS__.so.3.5.5 /usr/local/lib/libsiscardplugin1__ACS__.so.3 "  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libsiscardplugin1__ACS__.so.3.5.5 /usr/local/lib/libsiscardplugin1__ACS__.so.3.5"  >> pteid-pkg/install_pteid.sh



echo "install -m 755 -p \"lib/libpteidpkcs11.so.3.5.5\" \"/usr/local/lib/libpteidpkcs11.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidpkcs11.so.3.5.5 /usr/local/lib/libpteidpkcs11.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidpkcs11.so.3.5.5 /usr/local/lib/libpteidpkcs11.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidpkcs11.so.3.5.5 /usr/local/lib/libpteidpkcs11.so.3.5"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libpteidapplayer.so.3.5.5\" \"/usr/local/lib/libpteidapplayer.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidapplayer.so.3.5.5 /usr/local/lib/libpteidapplayer.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidapplayer.so.3.5.5 /usr/local/lib/libpteidapplayer.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidapplayer.so.3.5.5 /usr/local/lib/libpteidapplayer.so.3.5"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libpteidlib.so.3.5.5\" \"/usr/local/lib/libpteidlib.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidlib.so.3.5.5 /usr/local/lib/libpteidlib.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidlib.so.3.5.5 /usr/local/lib/libpteidlib.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidlib.so.3.5.5 /usr/local/lib/libpteidlib.so.3.5"  >> pteid-pkg/install_pteid.sh

echo "install -m 755 -p \"lib/libpteidlibJava_Wrapper.so.3.5.5\" \"/usr/local/lib/libpteidlibJava_Wrapper.so.3.5.5\""  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidlibJava_Wrapper.so.3.5.5 /usr/local/lib/libpteidlibJava_Wrapper.so"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidlibJava_Wrapper.so.3.5.5 /usr/local/lib/libpteidlibJava_Wrapper.so.3"  >> pteid-pkg/install_pteid.sh
echo "ln -s -f /usr/local/lib/libpteidlibJava_Wrapper.so.3.5.5 /usr/local/lib/libpteidlibJava_Wrapper.so.3.5"  >> pteid-pkg/install_pteid.sh



echo "install -m 755 -p \"bin/pteidgui\" \"/usr/local/bin/pteidgui\""  >> pteid-pkg/install_pteid.sh
echo ""  >> pteid-pkg/install_pteid.sh
echo "install -m 644 -p \"eidgui/eidmw_de.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "install -m 644 -p \"eidgui/eidmw_en.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "install -m 644 -p \"eidgui/eidmw_fr.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "install -m 644 -p \"eidgui/eidmw_nl.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "echo \"Finish!\""  >> pteid-pkg/install_pteid.sh


chmod +x pteid-pkg/install_pteid.sh




tar czvf pteid-pkg.tar.gz pteid-pkg/
