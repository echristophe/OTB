      subroutine solirr (wl,swl)
 
c     si (in w/m2/micron) contains the values of the solar
c     irradiance between 0.25 and 4.0 microns, by step of 0.0025 m.
c     the value of the total irradiance is 1372 w/m2 on the whole
c     spectrum (1358 w/m2 between 0.25 and 4.0 microns)
c
      dimension si(1501)
      logical ier
      real wl,swl,si,pas
      integer iwr,i,iwl
      common/sixs_ier/iwr,ier
 
      data (si(i),i=1,112) /
     a  69.30,  77.65,  86.00, 100.06, 114.12, 137.06, 160.00,
     a 169.52, 179.04, 178.02, 177.00, 193.69, 210.38, 241.69,
     a 273.00, 318.42, 363.84, 434.42, 505.00, 531.50, 558.00,
     a 547.50, 537.00, 559.02, 581.03, 619.52, 658.00, 694.39,
     a 730.78, 774.39, 817.99, 871.99, 925.99, 912.04, 898.09,
     a 920.69, 943.29, 925.99, 908.69, 936.09, 963.49, 994.94,
     a1026.39, 980.74, 935.09,1036.29,1137.49,1163.74,1189.99,
     a1109.34,1028.69,1088.99,1149.29,1033.69, 918.09,1031.89,
     a1145.69,1035.09, 924.49,1269.29,1614.09,1631.09,1648.09,
     a1677.19,1706.29,1744.89,1783.49,1750.19,1716.89,1705.19,
     a1693.49,1597.69,1501.89,1630.99,1760.09,1775.24,1790.39,
     a1859.94,1929.49,1993.44,2057.39,2039.23,2021.08,2030.73,
     a2040.38,2026.53,2012.68,1999.53,1986.38,2002.88,2019.38,
     a2038.09,2056.79,1967.74,1878.68,1905.83,1932.98,1953.58,
     a1974.18,1935.68,1897.19,1916.78,1936.38,1937.23,1938.09,
     a1881.44,1824.79,1814.09,1803.39,1832.24,1861.09,1885.93/
      data (si(i),i=113,224) /
     a1910.78,1904.68,1898.58,1875.73,1852.88,1865.64,1878.39,
     a1874.74,1871.09,1872.44,1873.79,1850.39,1826.99,1837.04,
     a1847.09,1841.18,1835.28,1849.48,1863.69,1851.03,1838.38,
     a1840.73,1843.08,1802.83,1762.58,1778.78,1794.99,1777.48,
     a1759.98,1764.73,1769.49,1753.48,1737.48,1713.14,1688.80,
     a1702.88,1716.97,1696.07,1675.17,1672.03,1668.89,1663.56,
     a1658.23,1647.75,1637.27,1630.02,1622.77,1606.06,1589.36,
     a1552.29,1515.22,1528.91,1542.60,1548.90,1555.21,1544.41,
     a1533.62,1525.24,1516.86,1507.92,1498.98,1484.07,1469.17,
     a1464.28,1459.39,1448.73,1438.08,1423.16,1408.24,1407.53,
     a1406.82,1397.82,1388.82,1378.51,1368.21,1352.13,1336.05,
     a1343.88,1351.71,1339.60,1327.50,1320.72,1313.94,1294.94,
     a1275.94,1280.92,1285.90,1278.04,1270.19,1263.68,1257.18,
     a1249.80,1242.41,1231.30,1220.19,1212.14,1204.10,1201.69,
     a1199.29,1194.78,1190.27,1185.47,1180.68,1174.38,1168.09,
     a1156.17,1144.26,1143.46,1142.67,1132.95,1123.23,1116.71/
      data (si(i),i=225,336) /
     a1110.19,1110.89,1111.59,1094.80,1078.01,1077.75,1077.49,
     a1073.89,1070.29,1058.71,1047.13,1045.66,1044.20,1037.03,
     a1029.86,1010.40, 990.94, 966.91, 942.89, 972.87,1002.86,
     a 978.93, 955.00, 960.95, 966.91, 983.31, 999.71, 991.91,
     a 984.11, 979.05, 973.99, 968.79, 963.60, 958.23, 952.87,
     a 947.93, 942.99, 937.99, 933.00, 928.00, 923.00, 918.18,
     a 913.37, 908.74, 904.11, 899.05, 893.99, 889.18, 884.37,
     a 879.74, 875.12, 870.24, 865.36, 860.94, 856.53, 852.02,
     a 847.50, 843.00, 838.50, 833.99, 829.49, 824.98, 820.48,
     a 815.99, 811.50, 806.99, 802.49, 798.17, 793.86, 789.74,
     a 785.63, 781.25, 776.87, 772.92, 768.98, 764.80, 760.63,
     a 756.06, 751.49, 746.99, 742.49, 738.18, 733.88, 729.76,
     a 725.63, 721.24, 716.86, 712.92, 708.99, 704.81, 700.63,
     a 696.25, 691.87, 687.94, 684.01, 680.01, 676.00, 671.80,
     a 667.61, 663.23, 658.86, 655.32, 651.77, 649.07, 646.37,
     a 643.74, 641.11, 638.05, 634.99, 632.18, 629.37, 626.74/
      data (si(i),i=337,448) /
     a 624.12, 621.06, 618.00, 615.18, 612.37, 609.92, 607.48,
     a 604.79, 602.11, 599.24, 596.38, 593.93, 591.48, 588.79,
     a 586.11, 583.25, 580.40, 577.94, 575.48, 572.99, 570.51,
     a 568.00, 565.49, 562.98, 560.47, 557.98, 555.50, 553.01,
     a 550.51, 548.00, 545.49, 542.98, 540.48, 537.98, 535.49,
     a 533.19, 530.90, 528.94, 526.99, 524.80, 522.62, 520.24,
     a 517.87, 515.44, 513.01, 509.59, 506.17, 502.89, 499.62,
     a 496.35, 493.09, 489.81, 486.54, 483.27, 480.01, 476.73,
     a 473.46, 470.19, 466.92, 463.64, 460.37, 457.10, 453.84,
     a 450.57, 447.30, 444.03, 440.76, 437.48, 434.21, 430.94,
     a 427.67, 424.40, 421.13, 417.86, 414.59, 411.32, 408.05,
     a 404.78, 401.51, 398.24, 394.97, 391.70, 388.43, 392.57,
     a 396.71, 401.92, 407.14, 405.32, 403.50, 401.67, 399.84,
     a 398.02, 396.21, 394.37, 392.54, 390.72, 388.90, 387.06,
     a 385.23, 383.42, 381.60, 379.77, 377.95, 376.12, 374.30,
     a 372.48, 370.66, 368.82, 366.99, 365.17, 363.35, 361.52/
      data (si(i),i=449,560) /
     a 359.69, 357.87, 356.05, 354.22, 352.39, 350.57, 348.75,
     a 346.92, 345.10, 343.27, 341.45, 341.84, 342.24, 342.95,
     a 343.66, 342.27, 340.89, 339.49, 338.09, 336.69, 335.30,
     a 333.91, 332.53, 331.13, 329.73, 328.34, 326.96, 325.56,
     a 324.16, 322.77, 321.39, 319.99, 318.59, 317.20, 315.82,
     a 314.42, 313.03, 311.63, 310.24, 308.85, 307.46, 306.06,
     a 304.66, 303.28, 301.90, 300.50, 299.10, 297.71, 296.32,
     a 294.93, 293.54, 293.41, 293.28, 293.35, 293.42, 292.26,
     a 291.10, 289.97, 288.84, 287.69, 286.54, 285.39, 284.25,
     a 283.10, 281.96, 280.81, 279.67, 278.52, 277.38, 276.23,
     a 275.08, 273.94, 272.80, 271.65, 270.51, 269.36, 268.22,
     a 267.07, 265.93, 264.78, 263.64, 262.49, 261.34, 260.20,
     a 259.06, 257.91, 256.77, 255.62, 254.47, 253.33, 252.20,
     a 251.16, 250.13, 249.11, 248.09, 246.97, 245.86, 244.74,
     a 243.61, 242.49, 241.37, 240.24, 239.12, 238.00, 236.89,
     a 235.76, 234.64, 233.51, 232.38, 231.26, 230.13, 229.01/
      data (si(i),i=561,672) /
     a 227.90, 226.77, 225.65, 224.53, 223.42, 222.29, 221.16,
     a 220.04, 218.92, 217.80, 216.68, 215.55, 214.43, 213.30,
     a 212.18, 211.06, 209.94, 208.82, 207.69, 206.99, 206.29,
     a 205.65, 205.02, 203.98, 202.95, 201.90, 200.85, 199.81,
     a 198.78, 197.74, 196.70, 195.65, 194.61, 193.57, 192.54,
     a 191.50, 190.47, 189.42, 188.37, 187.33, 186.30, 185.26,
     a 184.22, 183.18, 182.14, 181.10, 180.06, 179.02, 177.98,
     a 176.93, 175.89, 174.86, 173.83, 172.78, 171.73, 170.70,
     a 169.67, 168.62, 167.57, 167.59, 167.60, 167.76, 167.93,
     a 167.09, 166.26, 165.42, 164.58, 163.75, 162.92, 162.08,
     a 161.25, 160.41, 159.58, 158.74, 157.91, 157.07, 156.24,
     a 155.40, 154.57, 153.73, 152.90, 152.06, 151.23, 150.39,
     a 149.56, 148.72, 147.89, 147.06, 146.23, 145.39, 144.55,
     a 143.71, 142.88, 142.05, 141.22, 140.38, 139.54, 138.70,
     a 137.86, 137.99, 138.11, 138.36, 138.60, 137.94, 137.29,
     a 136.64, 136.00, 135.35, 134.71, 134.05, 133.39, 132.74/
      data (si(i),i=673,784) /
     a 132.09, 131.45, 130.81, 130.15, 129.49, 128.84, 128.20,
     a 127.55, 126.90, 126.25, 125.60, 124.94, 124.29, 123.64,
     a 123.00, 122.35, 121.70, 121.05, 120.40, 119.74, 119.09,
     a 118.45, 117.81, 117.15, 116.50, 115.85, 115.19, 115.25,
     a 115.31, 115.46, 115.62, 115.11, 114.60, 114.09, 113.58,
     a 113.06, 112.54, 112.03, 111.53, 111.01, 110.50, 109.99,
     a 109.47, 108.95, 108.44, 107.93, 107.42, 106.92, 106.42,
     a 105.89, 105.37, 104.85, 104.34, 103.83, 103.33, 102.81,
     a 102.29, 101.79, 101.29, 100.77, 100.25,  99.74,  99.22,
     a  98.71,  98.20,  97.69,  97.18,  97.12,  97.07,  97.09,
     a  97.11,  96.68,  96.26,  95.84,  95.42,  94.99,  94.56,
     a  94.14,  93.72,  93.31,  92.89,  92.46,  92.03,  91.61,
     a  91.19,  90.76,  90.34,  89.92,  89.49,  89.07,  88.66,
     a  88.24,  87.81,  87.39,  86.97,  86.55,  86.12,  85.69,
     a  85.26,  84.85,  84.43,  84.01,  83.59,  83.17,  82.75,
     a  82.32,  81.89,  81.89,  81.89,  81.95,  82.02,  81.68/
      data (si(i),i=785,896) /
     a  81.35,  81.00,  80.65,  80.32,  79.99,  79.64,  79.30,
     a  78.96,  78.61,  78.27,  77.94,  77.60,  77.26,  76.91,
     a  76.57,  76.24,  75.90,  75.56,  75.22,  74.88,  74.54,
     a  74.20,  73.86,  73.52,  73.18,  72.84,  72.50,  72.16,
     a  71.82,  71.48,  71.14,  70.80,  70.47,  70.13,  69.79,
     a  69.76,  69.73,  69.76,  69.80,  69.52,  69.24,  68.96,
     a  68.68,  68.41,  68.14,  67.85,  67.57,  67.29,  67.02,
     a  66.75,  66.48,  66.19,  65.90,  65.63,  65.36,  65.08,
     a  64.80,  64.53,  64.25,  63.97,  63.69,  63.41,  63.14,
     a  62.85,  62.57,  62.30,  62.03,  61.75,  61.47,  61.19,
     a  60.92,  60.64,  60.36,  60.08,  59.81,  59.80,  59.80,
     a  59.82,  59.85,  59.63,  59.40,  59.17,  58.95,  58.73,
     a  58.50,  58.28,  58.06,  57.83,  57.60,  57.37,  57.15,
     a  56.93,  56.70,  56.48,  56.26,  56.03,  55.79,  55.57,
     a  55.36,  55.13,  54.90,  54.66,  54.43,  54.22,  54.00,
     a  53.77,  53.55,  53.32,  53.09,  52.87,  52.65,  52.43/
      data (si(i),i=897,1008) /
     a  52.20,  51.97,  51.75,  51.72,  51.68,  51.67,  51.67,
     a  51.48,  51.30,  51.11,  50.92,  50.73,  50.55,  50.37,
     a  50.18,  49.98,  49.79,  49.61,  49.43,  49.23,  49.04,
     a  48.85,  48.67,  48.48,  48.30,  48.12,  47.93,  47.73,
     a  47.54,  47.36,  47.18,  46.98,  46.79,  46.60,  46.42,
     a  46.24,  46.06,  45.87,  45.67,  45.48,  45.30,  45.12,
     a  44.93,  44.87,  44.82,  44.80,  44.79,  44.62,  44.45,
     a  44.29,  44.14,  43.98,  43.83,  43.66,  43.49,  43.34,
     a  43.18,  43.02,  42.86,  42.70,  42.55,  42.38,  42.21,
     a  42.06,  41.90,  41.74,  41.58,  41.42,  41.26,  41.10,
     a  40.94,  40.78,  40.62,  40.46,  40.31,  40.14,  39.97,
     a  39.81,  39.66,  39.50,  39.34,  39.18,  39.03,  38.99,
     a  38.96,  38.94,  38.92,  38.79,  38.66,  38.52,  38.38,
     a  38.25,  38.12,  37.99,  37.86,  37.72,  37.58,  37.44,
     a  37.30,  37.17,  37.05,  36.91,  36.77,  36.64,  36.50,
     a  36.36,  36.23,  36.09,  35.96,  35.82,  35.69,  35.55/
      data (si(i),i=1009,1120) /
     a  35.42,  35.28,  35.15,  35.01,  34.88,  34.75,  34.61,
     a  34.47,  34.34,  34.20,  34.07,  34.05,  34.03,  34.03,
     a  34.03,  33.91,  33.79,  33.68,  33.57,  33.46,  33.35,
     a  33.23,  33.12,  33.01,  32.90,  32.78,  32.67,  32.55,
     a  32.44,  32.33,  32.23,  32.11,  32.00,  31.89,  31.77,
     a  31.66,  31.55,  31.43,  31.31,  31.20,  31.10,  30.99,
     a  30.87,  30.76,  30.66,  30.54,  30.42,  30.31,  30.20,
     a  30.08,  29.97,  29.93,  29.90,  29.88,  29.87,  29.76,
     a  29.66,  29.56,  29.46,  29.36,  29.27,  29.17,  29.08,
     a  28.98,  28.88,  28.77,  28.67,  28.58,  28.49,  28.39,
     a  28.30,  28.20,  28.10,  28.00,  27.91,  27.81,  27.71,
     a  27.61,  27.52,  27.41,  27.31,  27.21,  27.12,  27.03,
     a  26.93,  26.83,  26.74,  26.64,  26.54,  26.44,  26.35,
     a  26.33,  26.31,  26.29,  26.28,  26.20,  26.12,  26.04,
     a  25.95,  25.87,  25.79,  25.71,  25.64,  25.54,  25.45,
     a  25.37,  25.30,  25.21,  25.12,  25.05,  24.98,  24.89/
      data (si(i),i=1121,1232) /
     a  24.80,  24.71,  24.63,  24.55,  24.47,  24.39,  24.31,
     a  24.22,  24.14,  24.05,  23.97,  23.89,  23.81,  23.73,
     a  23.66,  23.56,  23.47,  23.39,  23.31,  23.28,  23.26,
     a  23.23,  23.21,  23.13,  23.06,  22.99,  22.92,  22.84,
     a  22.76,  22.69,  22.63,  22.55,  22.47,  22.41,  22.35,
     a  22.27,  22.19,  22.11,  22.04,  21.97,  21.90,  21.83,
     a  21.76,  21.68,  21.60,  21.53,  21.47,  21.39,  21.31,
     a  21.24,  21.18,  21.11,  21.03,  20.96,  20.89,  20.81,
     a  20.73,  20.66,  20.60,  20.57,  20.55,  20.54,  20.53,
     a  20.46,  20.40,  20.34,  20.28,  20.21,  20.14,  20.08,
     a  20.03,  19.96,  19.90,  19.83,  19.77,  19.71,  19.65,
     a  19.59,  19.53,  19.46,  19.39,  19.33,  19.27,  19.21,
     a  19.15,  19.08,  19.02,  18.96,  18.90,  18.84,  18.78,
     a  18.71,  18.64,  18.58,  18.53,  18.46,  18.40,  18.33,
     a  18.27,  18.26,  18.25,  18.24,  18.24,  18.19,  18.14,
     a  18.08,  18.03,  17.98,  17.93,  17.88,  17.83,  17.77/
      data (si(i),i=1233,1344) /
     a  17.71,  17.66,  17.62,  17.56,  17.50,  17.45,  17.41,
     a  17.35,  17.29,  17.25,  17.21,  17.14,  17.08,  17.04,
     a  17.00,  16.93,  16.87,  16.83,  16.79,  16.72,  16.66,
     a  16.61,  16.57,  16.51,  16.46,  16.41,  16.36,  16.34,
     a  16.33,  16.31,  16.30,  16.26,  16.22,  16.17,  16.13,
     a  16.08,  16.04,  16.00,  15.96,  15.90,  15.84,  15.81,
     a  15.78,  15.73,  15.68,  15.63,  15.59,  15.55,  15.50,
     a  15.45,  15.40,  15.36,  15.32,  15.28,  15.24,  15.18,
     a  15.13,  15.09,  15.05,  15.01,  14.96,  14.91,  14.87,
     a  14.82,  14.78,  14.73,  14.69,  14.66,  14.64,  14.64,
     a  14.63,  14.59,  14.55,  14.50,  14.45,  14.41,  14.38,
     a  14.35,  14.32,  14.26,  14.21,  14.18,  14.15,  14.10,
     a  14.05,  14.01,  13.98,  13.94,  13.91,  13.86,  13.82,
     a  13.78,  13.74,  13.70,  13.67,  13.62,  13.58,  13.54,
     a  13.50,  13.46,  13.43,  13.39,  13.35,  13.30,  13.25,
     a  13.22,  13.18,  13.17,  13.16,  13.14,  13.12,  13.09/
      data (si(i),i=1345,1456) /
     a  13.06,  13.03,  13.00,  12.96,  12.92,  12.89,  12.85,
     a  12.81,  12.78,  12.74,  12.70,  12.67,  12.65,  12.61,
     a  12.57,  12.53,  12.50,  12.46,  12.43,  12.39,  12.36,
     a  12.32,  12.28,  12.25,  12.22,  12.18,  12.15,  12.11,
     a  12.07,  12.04,  12.01,  11.97,  11.94,  11.90,  11.86,
     a  11.85,  11.85,  11.85,  11.84,  11.81,  11.78,  11.75,
     a  11.72,  11.69,  11.66,  11.63,  11.60,  11.58,  11.55,
     a  11.51,  11.47,  11.45,  11.42,  11.39,  11.36,  11.33,
     a  11.30,  11.27,  11.24,  11.21,  11.18,  11.15,  11.12,
     a  11.09,  11.06,  11.03,  11.00,  10.97,  10.94,  10.91,
     a  10.89,  10.85,  10.82,  10.78,  10.75,  10.73,  10.72,
     a  10.71,  10.70,  10.67,  10.64,  10.62,  10.59,  10.55,
     a  10.52,  10.50,  10.47,  10.44,  10.42,  10.39,  10.37,
     a  10.34,  10.31,  10.28,  10.25,  10.22,  10.20,  10.17,
     a  10.15,  10.12,  10.10,  10.06,  10.03,  10.00,   9.98,
     a   9.95,   9.92,   9.89,   9.86,   9.84,   9.82,   9.79/
      data (si(i),i=1457,1501) /
     a   9.75,   9.73,   9.71,   9.70,   9.70,   9.70,   9.70,
     a   9.67,   9.63,   9.61,   9.59,   9.58,   9.56,   9.53,
     a   9.50,   9.48,   9.45,   9.43,   9.41,   9.39,   9.36,
     a   9.34,   9.32,   9.30,   9.27,   9.24,   9.22,   9.20,
     a   9.18,   9.15,   9.13,   9.11,   9.08,   9.06,   9.05,
     a   9.02,   8.99,   8.96,   8.94,   8.92,   8.90,   8.87,
     a   8.85,   8.83,   8.81/
      pas=0.0025
      iwl=(wl-0.250)/pas+1.5
      if(iwl.lt.0) goto 10
      swl=si(iwl)
      return
10    write(iwr, 20)
      swl=si(1)
20    format(45h      wavelength  less  than  0.25  micron  :,/,
     a23hlet's take s(l)=s(0.25))
      return
      end
