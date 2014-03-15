ZTE Extract
===========

Extracts ZTE firmware installer packages that are shipped in Windows executable form for FTM mode flashing.

Useful to automate extracting and converting stock ROMs into ClockworkMod flashable zip packages.

Some tested installers that can be unpacked with this tool (inc. sha1):

    469e538f7d017b07b1b23969ba638455a98be83a  ZTE_Blade_Upgrade_Tool_V1.0.exe (Blade Froyo upgrade)
    6e53a581633765e3a9d6bd9f65cd924e809d3f5d  PSTW_DL_P729BSONV1.0.0B02.exe (Blade Froyo upgrade for Tele2 customers)
    d129bada252c587fc6df1134aa7b9968ca5ad608  Sales_DL_P729B_Finland_Elisa_V1.00.01.exe (Blade Froyo upgrade for Saunalahti/Elisa customers)
    41a14e2eb07262bd241a5c401fe6e87dfa0f5664  ZTE_Light_Upgrade_Tools_V1.1.exe (Light Froyo ugprade for TELIA customers)
    8efeb2d9dc67904559f38089eab4cc37e08411f8  DL_TaniaV1.00.00.exe (Tania upgrade for generic software)

Usage
-----
`zte_extract l ZTE_Blade_Upgrade_Tool_V1.0.exe` lists all files in the archive  
`zte_extract x ZTE_Blade_Upgrade_Tool_V1.0.exe` extracts all files from the archive  
`zte_extract x ZTE_Blade_Upgrade_Tool_V1.0.exe boot.img system.img` extracts boot.img and system.img from the archive  

Example
-------
    $ ./zte_extract l ZTE_Blade_Upgrade_Tool_V1.0.exe                           
    Length     MD5                              Name
    ----------------------------------------------------------------------
           591 CEA3A3F03868EB7E172A3407FAD8D14A SMT
       4667479 5BEB873B7657EFFE3D4EF482672F3EB1 driverinstaller.exe
           120 DAA3708D3E4D2AB83C818C2F318AEA3D RecordCSV.sdi
        208896 8FCEF63FFEDA8C86260B6E7B9C13DC8B xcsp_eclib.dll
        174488 4A1012D9DD2AB51C742FBB4F9C0F56E5 armprgZTE.bin
       6512640 BE364140301D7DD2A232598502D1BF87 download.exe
        409600 4BC55796584D5707EEFC528AB2B960F8 Launcher.exe
         78296 933EE5C2D98F424B7C2F4E04A82FAA51 WCDMA_DL_Setting.cfg
      17510400 A4280A61A7DF31203C60F8FA6583EE8B amss.mbn
            40 E088F1390C90410E7234CFE1E58E1302 amsshd.mbn
         52040 862E5BCEFE7A18B6661539E209B914AA appsboot.mbn
            40 477CE0D8239C9EEB6940C519C91C0932 appsboothd.mbn
       3446784 F20579998076103C92057AE886FE9134 boot.img
        577536 F74733E06F81890BBA82D1FB29B2393F cefs.mbn
        523096 FCBB10E605C6BD14AFACA852FB6C3449 oemsbl.mbn
            40 E0DA4B054D1E43A7AE59CDC3B04FB2E9 oemsblhd.mbn
           464 8725B041C4677F32F653510F3A592D28 partition.mbn
           308 96630DC3EB8425B15E3F5B29CBEC6B02 partition_zte.mbn
         57328 B9D84951A74331622F92DA85196355F0 qcsbl.mbn
         11412 D10D5D6A5CEF6B987853FAF0F9AC490E qcsblhd_cfgdata.mbn
       3837952 4347C70767377F1C4809A42A882B81C5 recovery.img
        770048 6517E43357B2CCB1E3C23CE1AF67F1E5 splash.img
     162503616 54C22B124081A348525F6716A9AB84D1 system.img
    ----------------------------------------------------------------------
     201343214                                  23 files

Sources
-------
http://www.ztesweden.se/Exego.aspx?p_id=327  
http://www.elisa.fi/elisa/docimages/attachment/tuki/Sales_DL_P729B_Finland_Elisa_V1.00.01.exe  
