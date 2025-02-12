#include "csvparser.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CSVParser::CSVParser()
{
    // The CSV data from your React app would be stored in a resource file
    collegeData = R"(Starting College,Ending College,Distance Between
Arizona State University,Columbia University,747
Arizona State University,Duke University,1741
Arizona State University,Harvard University,1704
Arizona State University,Massachusetts Institute of Technology (MIT),2636
Arizona State University,Massachusetts Institute of Technology (MIT),2529
Arizona State University,Northwestern,1756
Arizona State University,Northwestern,1345
Arizona State University,Ohio State University,1865
Arizona State University,Ohio State University,2654
Arizona State University,Saddleback College,379
Arizona State University,Saddleback College,329
Arizona State University,Stanford University,2710
Arizona State University,University of  Michigan,1956
Arizona State University,University of  Michigan,2134
Arizona State University,University of California, Berkeley,1583
Arizona State University,University of California, Irvine (UCI),375
Arizona State University,University of California, Irvine (UCI),2841
Arizona State University,University of California, Los Angeles (UCLA),397
Arizona State University,University of California, Los Angeles (UCLA),1737
Arizona State University,University of Chicago,774
Arizona State University,University of Florida,164
Arizona State University,University of Oregon,1343
Arizona State University,University of Oregon,64
Arizona State University,University of Oregon,1286
Arizona State University,University of Texas at Austin,1433
Arizona State University,University of the Pacific,720
Arizona State University,University of the Pacific,1162
Arizona State University,University of Wisconsin,1684
Arizona State University,University of Wisconsin,2717
Arizona State University,Yale University,540
Columbia University,Arizona State University,747
Columbia University,Duke University,2862
Columbia University,Harvard University,265
Columbia University,Massachusetts Institute of Technology (MIT),677
Columbia University,Northwestern,301
Columbia University,Ohio State University,2578
Columbia University,Saddleback College,2388
Columbia University,Stanford University,1184
Columbia University,University of  Michigan,869
Columbia University,University of California, Berkeley,1289
Columbia University,University of California, Irvine (UCI),524
Columbia University,University of California, Los Angeles (UCLA),2303
Columbia University,University of Chicago,1304
Columbia University,University of Florida,1806
Columbia University,University of Oregon,1253
Columbia University,University of Oregon,1310
Columbia University,University of Texas at Austin,1550
Columbia University,University of the Pacific,1957
Columbia University,University of Wisconsin,70
Columbia University,Yale University,2177
Duke University,Arizona State University,1741
Duke University,Columbia University,2862
Duke University,Harvard University,416
Duke University,Massachusetts Institute of Technology (MIT),2838
Duke University,Northwestern,1053
Duke University,Ohio State University,1329
Duke University,Saddleback College,2883
Duke University,Stanford University,2770
Duke University,University of  Michigan,2292
Duke University,University of California, Berkeley,2764
Duke University,University of California, Irvine (UCI),861
Duke University,University of California, Los Angeles (UCLA),1143
Duke University,University of Chicago,1393
Duke University,University of Florida,1905
Duke University,University of Oregon,1665
Duke University,University of Oregon,99
Duke University,University of Texas at Austin,703
Duke University,University of the Pacific,2852
Duke University,University of Wisconsin,2056
Duke University,Yale University,2718
Harvard University,Arizona State University,1704
Harvard University,Columbia University,265
Harvard University,Duke University,416
Harvard University,Massachusetts Institute of Technology (MIT),1985
Harvard University,Northwestern,2785
Harvard University,Ohio State University,2918
Harvard University,Saddleback College,575
Harvard University,Stanford University,1191
Harvard University,University of  Michigan,944
Harvard University,University of California, Berkeley,1851
Harvard University,University of California, Irvine (UCI),1300
Harvard University,University of California, Los Angeles (UCLA),668
Harvard University,University of Chicago,503
Harvard University,University of Florida,316
Harvard University,University of Oregon,565
Harvard University,University of Oregon,1132
Harvard University,University of Texas at Austin,601
Harvard University,University of the Pacific,1732
Harvard University,University of Wisconsin,2918
Harvard University,Yale University,2461
Massachusetts Institute of Technology (MIT),Arizona State University,2636
Massachusetts Institute of Technology (MIT),Arizona State University,2529
Massachusetts Institute of Technology (MIT),Columbia University,677
Massachusetts Institute of Technology (MIT),Duke University,2838
Massachusetts Institute of Technology (MIT),Harvard University,1985
Massachusetts Institute of Technology (MIT),Northwestern,993
Massachusetts Institute of Technology (MIT),Northwestern,1248
Massachusetts Institute of Technology (MIT),Ohio State University,772
Massachusetts Institute of Technology (MIT),Ohio State University,1782
Massachusetts Institute of Technology (MIT),Saddleback College,2989
Massachusetts Institute of Technology (MIT),Saddleback College,1140
Massachusetts Institute of Technology (MIT),Stanford University,1880
Massachusetts Institute of Technology (MIT),University of  Michigan,803
Massachusetts Institute of Technology (MIT),University of  Michigan,2602
Massachusetts Institute of Technology (MIT),University of California, Berkeley,1952
Massachusetts Institute of Technology (MIT),University of California, Irvine (UCI),2986
Massachusetts Institute of Technology (MIT),University of California, Irvine (UCI),1193
Massachusetts Institute of Technology (MIT),University of California, Los Angeles (UCLA),2998
Massachusetts Institute of Technology (MIT),University of California, Los Angeles (UCLA),948
Massachusetts Institute of Technology (MIT),University of Chicago,1760
Massachusetts Institute of Technology (MIT),University of Florida,2271
Massachusetts Institute of Technology (MIT),University of Oregon,3107
Massachusetts Institute of Technology (MIT),University of Oregon,2773
Massachusetts Institute of Technology (MIT),University of Oregon,373
Massachusetts Institute of Technology (MIT),University of Texas at Austin,1825
Massachusetts Institute of Technology (MIT),University of the Pacific,3057
Massachusetts Institute of Technology (MIT),University of the Pacific,2462
Massachusetts Institute of Technology (MIT),University of Wisconsin,1125
Massachusetts Institute of Technology (MIT),University of Wisconsin,1000
Massachusetts Institute of Technology (MIT),Yale University,2170
Northwestern,Arizona State University,1756
Northwestern,Arizona State University,1345
Northwestern,Columbia University,301
Northwestern,Duke University,1053
Northwestern,Harvard University,2785
Northwestern,Massachusetts Institute of Technology (MIT),993
Northwestern,Massachusetts Institute of Technology (MIT),1248
Northwestern,Ohio State University,335
Northwestern,Ohio State University,1453
Northwestern,Saddleback College,2033
Northwestern,Saddleback College,1925
Northwestern,Stanford University,1712
Northwestern,University of  Michigan,270
Northwestern,University of  Michigan,1614
Northwestern,University of California, Berkeley,1769
Northwestern,University of California, Irvine (UCI),2030
Northwestern,University of California, Irvine (UCI),173
Northwestern,University of California, Los Angeles (UCLA),2043
Northwestern,University of California, Los Angeles (UCLA),1504
Northwestern,University of Chicago,192
Northwestern,University of Florida,392
Northwestern,University of Oregon,2151
Northwestern,University of Oregon,1366
Northwestern,University of Oregon,2954
Northwestern,University of Texas at Austin,2699
Northwestern,University of the Pacific,2102
Northwestern,University of the Pacific,2828
Northwestern,University of Wisconsin,145
Northwestern,University of Wisconsin,907
Northwestern,Yale University,1401
Ohio State University,Arizona State University,1865
Ohio State University,Arizona State University,2654
Ohio State University,Columbia University,2578
Ohio State University,Duke University,1329
Ohio State University,Harvard University,2918
Ohio State University,Massachusetts Institute of Technology (MIT),772
Ohio State University,Massachusetts Institute of Technology (MIT),1782
Ohio State University,Northwestern,335
Ohio State University,Northwestern,1453
Ohio State University,Saddleback College,2252
Ohio State University,Saddleback College,1238
Ohio State University,Stanford University,360
Ohio State University,University of  Michigan,184
Ohio State University,University of  Michigan,2457
Ohio State University,University of California, Berkeley,1800
Ohio State University,University of California, Irvine (UCI),2248
Ohio State University,University of California, Irvine (UCI),1467
Ohio State University,University of California, Los Angeles (UCLA),2261
Ohio State University,University of California, Los Angeles (UCLA),57
Ohio State University,University of Chicago,570
Ohio State University,University of Florida,1818
Ohio State University,University of Oregon,2241
Ohio State University,University of Oregon,853
Ohio State University,University of Oregon,2690
Ohio State University,University of Texas at Austin,839
Ohio State University,University of the Pacific,2412
Ohio State University,University of the Pacific,173
Ohio State University,University of Wisconsin,503
Ohio State University,University of Wisconsin,2444
Ohio State University,Yale University,2517
Saddleback College,Arizona State University,379
Saddleback College,Arizona State University,329
Saddleback College,Columbia University,2388
Saddleback College,Duke University,2883
Saddleback College,Harvard University,575
Saddleback College,Massachusetts Institute of Technology (MIT),2989
Saddleback College,Massachusetts Institute of Technology (MIT),1140
Saddleback College,Northwestern,2033
Saddleback College,Northwestern,1925
Saddleback College,Ohio State University,2252
Saddleback College,Ohio State University,1238
Saddleback College,Stanford University,650
Saddleback College,University of  Michigan,2249
Saddleback College,University of  Michigan,2356
Saddleback College,University of California, Berkeley,1705
Saddleback College,University of California, Irvine (UCI),16
Saddleback College,University of California, Irvine (UCI),2128
Saddleback College,University of California, Los Angeles (UCLA),66
Saddleback College,University of California, Los Angeles (UCLA),2211
Saddleback College,University of Chicago,2002
Saddleback College,University of Florida,2562
Saddleback College,University of Oregon,906
Saddleback College,University of Oregon,1577
Saddleback College,University of Oregon,434
Saddleback College,University of Texas at Austin,2686
Saddleback College,University of the Pacific,390
Saddleback College,University of the Pacific,2871
Saddleback College,University of Wisconsin,1981
Saddleback College,University of Wisconsin,668
Saddleback College,Yale University,481
Stanford University,Arizona State University,2710
Stanford University,Columbia University,1184
Stanford University,Duke University,2770
Stanford University,Harvard University,1191
Stanford University,Massachusetts Institute of Technology (MIT),1880
Stanford University,Northwestern,1712
Stanford University,Ohio State University,360
Stanford University,Saddleback College,650
Stanford University,University of  Michigan,1809
Stanford University,University of California, Berkeley,1845
Stanford University,University of California, Irvine (UCI),1062
Stanford University,University of California, Los Angeles (UCLA),2525
Stanford University,University of Chicago,2242
Stanford University,University of Florida,2271
Stanford University,University of Oregon,794
Stanford University,University of Oregon,2632
Stanford University,University of Texas at Austin,470
Stanford University,University of the Pacific,884
Stanford University,University of Wisconsin,661
Stanford University,Yale University,368
University of  Michigan,Arizona State University,1956
University of  Michigan,Arizona State University,2134
University of  Michigan,Columbia University,869
University of  Michigan,Duke University,2292
University of  Michigan,Harvard University,944
University of  Michigan,Massachusetts Institute of Technology (MIT),803
University of  Michigan,Massachusetts Institute of Technology (MIT),2602
University of  Michigan,Northwestern,270
University of  Michigan,Northwestern,1614
University of  Michigan,Ohio State University,184
University of  Michigan,Ohio State University,2457
University of  Michigan,Saddleback College,2249
University of  Michigan,Saddleback College,2356
University of  Michigan,Stanford University,1809
University of  Michigan,University of California, Berkeley,1964
University of  Michigan,University of California, Irvine (UCI),2245
University of  Michigan,University of California, Irvine (UCI),1452
University of  Michigan,University of California, Los Angeles (UCLA),2252
University of  Michigan,University of California, Los Angeles (UCLA),401
University of  Michigan,University of Chicago,2484
University of  Michigan,University of Florida,1765
University of  Michigan,University of Oregon,2347
University of  Michigan,University of Oregon,2528
University of  Michigan,University of Oregon,1576
University of  Michigan,University of Texas at Austin,406
University of  Michigan,University of the Pacific,2318
University of  Michigan,University of the Pacific,2528
University of  Michigan,University of Wisconsin,391
University of  Michigan,University of Wisconsin,1295
University of  Michigan,Yale University,2547
University of California, Berkeley,Arizona State University,1583
University of California, Berkeley,Columbia University,1289
University of California, Berkeley,Duke University,2764
University of California, Berkeley,Harvard University,1851
University of California, Berkeley,Massachusetts Institute of Technology (MIT),1952
University of California, Berkeley,Northwestern,1769
University of California, Berkeley,Ohio State University,1800
University of California, Berkeley,Saddleback College,1705
University of California, Berkeley,Stanford University,1845
University of California, Berkeley,University of  Michigan,1964
University of California, Berkeley,University of California, Irvine (UCI),2213
University of California, Berkeley,University of California, Los Angeles (UCLA),1724
University of California, Berkeley,University of Chicago,737
University of California, Berkeley,University of Florida,1694
University of California, Berkeley,University of Oregon,268
University of California, Berkeley,University of Oregon,2782
University of California, Berkeley,University of Texas at Austin,2288
University of California, Berkeley,University of the Pacific,2029
University of California, Berkeley,University of Wisconsin,2040
University of California, Berkeley,Yale University,1926
University of California, Irvine (UCI),Arizona State University,375
University of California, Irvine (UCI),Arizona State University,2841
University of California, Irvine (UCI),Columbia University,524
University of California, Irvine (UCI),Duke University,861
University of California, Irvine (UCI),Harvard University,1300
University of California, Irvine (UCI),Massachusetts Institute of Technology (MIT),2986
University of California, Irvine (UCI),Massachusetts Institute of Technology (MIT),1193
University of California, Irvine (UCI),Northwestern,2030
University of California, Irvine (UCI),Northwestern,173
University of California, Irvine (UCI),Ohio State University,2248
University of California, Irvine (UCI),Ohio State University,1467
University of California, Irvine (UCI),Saddleback College,16
University of California, Irvine (UCI),Saddleback College,2128
University of California, Irvine (UCI),Stanford University,1062
University of California, Irvine (UCI),University of  Michigan,2245
University of California, Irvine (UCI),University of  Michigan,1452
University of California, Irvine (UCI),University of California, Berkeley,2213
University of California, Irvine (UCI),University of California, Los Angeles (UCLA),51
University of California, Irvine (UCI),University of California, Los Angeles (UCLA),2078
University of California, Irvine (UCI),University of Chicago,1949
University of California, Irvine (UCI),University of Florida,788
University of California, Irvine (UCI),University of Oregon,899
University of California, Irvine (UCI),University of Oregon,878
University of California, Irvine (UCI),University of Oregon,1992
University of California, Irvine (UCI),University of Texas at Austin,1505
University of California, Irvine (UCI),University of the Pacific,383
University of California, Irvine (UCI),University of the Pacific,1538
University of California, Irvine (UCI),University of Wisconsin,1978
University of California, Irvine (UCI),University of Wisconsin,146
University of California, Irvine (UCI),Yale University,224
University of California, Los Angeles (UCLA),Arizona State University,397
University of California, Los Angeles (UCLA),Arizona State University,1737
University of California, Los Angeles (UCLA),Columbia University,2303
University of California, Los Angeles (UCLA),Duke University,1143
University of California, Los Angeles (UCLA),Harvard University,668
University of California, Los Angeles (UCLA),Massachusetts Institute of Technology (MIT),2998
University of California, Los Angeles (UCLA),Massachusetts Institute of Technology (MIT),948
University of California, Los Angeles (UCLA),Northwestern,2043
University of California, Los Angeles (UCLA),Northwestern,1504
University of California, Los Angeles (UCLA),Ohio State University,2261
University of California, Los Angeles (UCLA),Ohio State University,57
University of California, Los Angeles (UCLA),Saddleback College,66.3
University of California, Los Angeles (UCLA),Saddleback College,2211
University of California, Los Angeles (UCLA),Stanford University,2525
University of California, Los Angeles (UCLA),University of  Michigan,2252
University of California, Los Angeles (UCLA),University of  Michigan,401
University of California, Los Angeles (UCLA),University of California, Berkeley,1724
University of California, Los Angeles (UCLA),University of California, Irvine (UCI),51.5
University of California, Los Angeles (UCLA),University of California, Irvine (UCI),2078
University of California, Los Angeles (UCLA),University of Chicago,682
University of California, Los Angeles (UCLA),University of Florida,2998
University of California, Los Angeles (UCLA),University of Oregon,849
University of California, Los Angeles (UCLA),University of Oregon,1127
University of California, Los Angeles (UCLA),University of Oregon,558
University of California, Los Angeles (UCLA),University of Texas at Austin,916
University of California, Los Angeles (UCLA),University of the Pacific,333
University of California, Los Angeles (UCLA),University of the Pacific,802
University of California, Los Angeles (UCLA),University of Wisconsin,1991
University of California, Los Angeles (UCLA),University of Wisconsin,911
University of California, Los Angeles (UCLA),Yale University,2146
University of Chicago,Arizona State University,774
University of Chicago,Columbia University,1304
University of Chicago,Duke University,1393
University of Chicago,Harvard University,503
University of Chicago,Massachusetts Institute of Technology (MIT),1760
University of Chicago,Northwestern,192
University of Chicago,Ohio State University,570
University of Chicago,Saddleback College,2002
University of Chicago,Stanford University,2242
University of Chicago,University of  Michigan,2484
University of Chicago,University of California, Berkeley,737
University of Chicago,University of California, Irvine (UCI),1949
University of Chicago,University of California, Los Angeles (UCLA),682
University of Chicago,University of Florida,1622
University of Chicago,University of Oregon,2157
University of Chicago,University of Oregon,293
University of Chicago,University of Texas at Austin,1870
University of Chicago,University of the Pacific,1707
University of Chicago,University of Wisconsin,954
University of Chicago,Yale University,1620
University of Florida,Arizona State University,164
University of Florida,Columbia University,1806
University of Florida,Duke University,1905
University of Florida,Harvard University,316
University of Florida,Massachusetts Institute of Technology (MIT),2271
University of Florida,Northwestern,392
University of Florida,Ohio State University,1818
University of Florida,Saddleback College,2562
University of Florida,Stanford University,2271
University of Florida,University of  Michigan,1765
University of Florida,University of California, Berkeley,1694
University of Florida,University of California, Irvine (UCI),788
University of Florida,University of California, Los Angeles (UCLA),2998
University of Florida,University of Chicago,1622
University of Florida,University of Oregon,1767
University of Florida,University of Oregon,2736
University of Florida,University of Texas at Austin,2489
University of Florida,University of the Pacific,429
University of Florida,University of Wisconsin,1854
University of Florida,Yale University,2733
University of Oregon,Arizona State University,1343
University of Oregon,Arizona State University,64
University of Oregon,Arizona State University,1286
University of Oregon,Columbia University,1253
University of Oregon,Columbia University,1310
University of Oregon,Duke University,1665
University of Oregon,Duke University,99
University of Oregon,Harvard University,565
University of Oregon,Harvard University,1132
University of Oregon,Massachusetts Institute of Technology (MIT),3107
University of Oregon,Massachusetts Institute of Technology (MIT),2773
University of Oregon,Massachusetts Institute of Technology (MIT),373
University of Oregon,Northwestern,2151
University of Oregon,Northwestern,1366
University of Oregon,Northwestern,2954
University of Oregon,Ohio State University,2241
University of Oregon,Ohio State University,853
University of Oregon,Ohio State University,2690
University of Oregon,Saddleback College,906
University of Oregon,Saddleback College,1577
University of Oregon,Saddleback College,434
University of Oregon,Stanford University,794
University of Oregon,Stanford University,2632
University of Oregon,University of  Michigan,2347
University of Oregon,University of  Michigan,2528
University of Oregon,University of  Michigan,1576
University of Oregon,University of California, Berkeley,268
University of Oregon,University of California, Berkeley,2782
University of Oregon,University of California, Irvine (UCI),899
University of Oregon,University of California, Irvine (UCI),878
University of Oregon,University of California, Irvine (UCI),1992
University of Oregon,University of California, Los Angeles (UCLA),849
University of Oregon,University of California, Los Angeles (UCLA),1127
University of Oregon,University of California, Los Angeles (UCLA),558
University of Oregon,University of Chicago,2157
University of Oregon,University of Chicago,293
University of Oregon,University of Florida,1767
University of Oregon,University of Florida,2736
University of Oregon,University of Oregon,140
University of Oregon,University of Oregon,140
University of Oregon,University of Texas at Austin,243
University of Oregon,University of Texas at Austin,2051
University of Oregon,University of the Pacific,517
University of Oregon,University of the Pacific,809
University of Oregon,University of the Pacific,1857
University of Oregon,University of Wisconsin,2111
University of Oregon,University of Wisconsin,2480
University of Oregon,University of Wisconsin,377
University of Oregon,Yale University,1674
University of Oregon,Yale University,472
University of Texas at Austin,Arizona State University,1433
University of Texas at Austin,Columbia University,1550
University of Texas at Austin,Duke University,703
University of Texas at Austin,Harvard University,601
University of Texas at Austin,Massachusetts Institute of Technology (MIT),1825
University of Texas at Austin,Northwestern,2699
University of Texas at Austin,Ohio State University,839
University of Texas at Austin,Saddleback College,2686
University of Texas at Austin,Stanford University,470
University of Texas at Austin,University of  Michigan,406
University of Texas at Austin,University of California, Berkeley,2288
University of Texas at Austin,University of California, Irvine (UCI),1505
University of Texas at Austin,University of California, Los Angeles (UCLA),916
University of Texas at Austin,University of Chicago,1870
University of Texas at Austin,University of Florida,2489
University of Texas at Austin,University of Oregon,243
University of Texas at Austin,University of Oregon,2051
University of Texas at Austin,University of the Pacific,1621
University of Texas at Austin,University of Wisconsin,623
University of Texas at Austin,Yale University,2998
University of the Pacific,Arizona State University,720
University of the Pacific,Arizona State University,1162
University of the Pacific,Columbia University,1957
University of the Pacific,Duke University,2852
University of the Pacific,Harvard University,1732
University of the Pacific,Massachusetts Institute of Technology (MIT),3057
University of the Pacific,Massachusetts Institute of Technology (MIT),2462
University of the Pacific,Northwestern,2102
University of the Pacific,Northwestern,2828
University of the Pacific,Ohio State University,2412
University of the Pacific,Ohio State University,173
University of the Pacific,Saddleback College,390
University of the Pacific,Saddleback College,2871
University of the Pacific,Stanford University,884
University of the Pacific,University of  Michigan,2318
University of the Pacific,University of  Michigan,2528
University of the Pacific,University of California, Berkeley,2029
University of the Pacific,University of California, Irvine (UCI),383
University of the Pacific,University of California, Irvine (UCI),1538
University of the Pacific,University of California, Los Angeles (UCLA),333
University of the Pacific,University of California, Los Angeles (UCLA),802
University of the Pacific,University of Chicago,1707
University of the Pacific,University of Florida,429
University of the Pacific,University of Oregon,517
University of the Pacific,University of Oregon,809
University of the Pacific,University of Oregon,1857
University of the Pacific,University of Texas at Austin,1621
University of the Pacific,University of Wisconsin,2052
University of the Pacific,University of Wisconsin,2723
University of the Pacific,Yale University,1032
University of Wisconsin,Arizona State University,1684
University of Wisconsin,Arizona State University,2717
University of Wisconsin,Columbia University,70
University of Wisconsin,Duke University,2056
University of Wisconsin,Harvard University,2918
University of Wisconsin,Massachusetts Institute of Technology (MIT),1125
University of Wisconsin,Massachusetts Institute of Technology (MIT),1000
University of Wisconsin,Northwestern,145
University of Wisconsin,Northwestern,907
University of Wisconsin,Ohio State University,503
University of Wisconsin,Ohio State University,2444
University of Wisconsin,Saddleback College,1981
University of Wisconsin,Saddleback College,668
University of Wisconsin,Stanford University,661
University of Wisconsin,University of  Michigan,391
University of Wisconsin,University of  Michigan,1295
University of Wisconsin,University of California, Berkeley,2040
University of Wisconsin,University of California, Irvine (UCI),1978
University of Wisconsin,University of California, Irvine (UCI),146
University of Wisconsin,University of California, Los Angeles (UCLA),1991
University of Wisconsin,University of California, Los Angeles (UCLA),911
University of Wisconsin,University of Chicago,954
University of Wisconsin,University of Florida,1854
University of Wisconsin,University of Oregon,2111
University of Wisconsin,University of Oregon,2480
University of Wisconsin,University of Oregon,377
University of Wisconsin,University of Texas at Austin,623
University of Wisconsin,University of the Pacific,2052
University of Wisconsin,University of the Pacific,2723
University of Wisconsin,Yale University,1320
Yale University,Arizona State University,540
Yale University,Columbia University,2177
Yale University,Duke University,2718
Yale University,Harvard University,2461
Yale University,Massachusetts Institute of Technology (MIT),2170
Yale University,Northwestern,1401
Yale University,Ohio State University,2517
Yale University,Saddleback College,481
Yale University,Stanford University,368
Yale University,University of  Michigan,2547
Yale University,University of California, Berkeley,1926
Yale University,University of California, Irvine (UCI),224
Yale University,University of California, Los Angeles (UCLA),2146
Yale University,University of Chicago,1620
Yale University,University of Florida,2733
Yale University,University of Oregon,1674
Yale University,University of Oregon,472
Yale University,University of Texas at Austin,2998
Yale University,University of the Pacific,1032
Yale University,University of Wisconsin,1320)"; // Include the full CSV data here
}

QPair<QMap<QString, QMap<QString, double>>, QSet<QString>> CSVParser::parseCollegeData()
{
    QMap<QString, QMap<QString, double>> distanceMap;
    QSet<QString> uniqueColleges;

    QTextStream stream(&collegeData);
    QString line = stream.readLine(); // Skip header

    while (!stream.atEnd()) {
        line = stream.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 3) {
            QString start = fields[0].trimmed();
            QString end = fields[1].trimmed();
            double distance = fields[2].toDouble();

            if (!start.isEmpty() && !end.isEmpty() && distance > 0) {
                distanceMap[start][end] = distance;
                uniqueColleges.insert(start);
                uniqueColleges.insert(end);
            }
        }
    }

    return qMakePair(distanceMap, uniqueColleges);
}
