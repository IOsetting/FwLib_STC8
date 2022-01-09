# STC8H 通道和精度

| 系列              |   精度 |  通道数      |
|  ---------------- | ---------- | -------------- | 
| STC8H1K08 series     | 10-bit     |    9 channels  |
| STC8H1K28 series     | 10-bit     |    12 channels |   
| STC8H3K64S4 series   | 12-bit     |    12 channels |   
| STC8H3K64S2 series   | 12-bit     |    12 channels |   
| STC8H8K64U series    | 12-bit     |    15 channels |   
| STC8H2K64T series    | 12-bit     |    15 channels |   
| STC8H4K64TLR series  | 12-bit     |    15 channels |   
| STC8H4K64TLCD series | 12-bit     |    15 channels |   
| STC8H4K64LCD series  | 12-bit     |    15 channels | 


# STC8G/STC8H ADC 通道对应关系

|       |   STC8H1K28  | STC8H1K08    | STC8H3K64S4<br>STC8H3K64S2    | STC8H8K64U<br>STC8H2K64T<br>STC8H4K64TLR    | STC8H4K64TLCD<br>STC8H4K64LCD   | STC8G1K08A | STC8G1K08<br>STC8G1K08T   | STC8G2K64S4<br>STC8G2K64S2 |     
|  ---- | ------------ | ------------ | -------------- | --------------- | -------------- | ---------- | -----------  | ----------- |             
|  0000 | P1.0/ADC0    |  P1.0/ADC0   |  P1.0/ADC0     |  P1.0/ADC0      |  P1.0/ADC0     |  P3.0/ADC0 |  P1.0/ADC0   |  P1.0/ADC0  |                    
|  0001 | P1.1/ADC1    |  P1.1/ADC1   |  P1.1/ADC1     |  P1.1/ADC1      |  P1.1/ADC1     |  P3.1/ADC1 |  P1.1/ADC1   |  P1.1/ADC1  |                    
|  0010 | P1.2/ADC2    |  N/A         |  P1.2/ADC2     |  P5.4/ADC2      |  P5.4/ADC2     |  P3.2/ADC2 |  P1.2/ADC2   |  P1.2/ADC2  |              
|  0011 | P1.3/ADC3    |  N/A         |  N/A           |  P1.3/ADC3      |  P1.3/ADC3     |  P3.3/ADC3 |  P1.3/ADC3   |  P1.3/ADC3  |                
|  0100 | P1.4/ADC4    |  N/A         |  N/A           |  P1.4/ADC4      |  P1.4/ADC4     |  P5.4/ADC4 |  P1.4/ADC4   |  P1.4/ADC4  |                 
|  0101 | P1.5/ADC5    |  N/A         |  N/A           |  P1.5/ADC5      |  P1.5/ADC5     |  P5.5/ADC5 |  P1.5/ADC5   |  P1.5/ADC5  |                   
|  0110 | P1.6/ADC6    |  N/A         |  P1.6/ADC6     |  P1.6/ADC6      |  P6.2/ADC6     |  N/A       |  P1.6/ADC6   |  P1.6/ADC6  |        
|  0111 | P1.7/ADC7    |  N/A         |  P1.7/ADC7     |  P1.7/ADC7      |  P6.3/ADC7     |  N/A       |  P1.7/ADC7   |  P1.7/ADC7  |        
|  1000 | P0.0/ADC8    |  P3.0/ADC8   |  P0.0/ADC8     |  P0.0/ADC8      |  P0.0/ADC8     |  N/A       |  P3.0/ADC8   |  P0.0/ADC8  |              
|  1001 | P0.1/ADC9    |  P3.1/ADC9   |  P0.1/ADC9     |  P0.1/ADC9      |  P0.1/ADC9     |  N/A       |  P3.1/ADC9   |  P0.1/ADC9  |              
|  1010 | P0.2/ADC10   |  P3.2/ADC10  |  P0.2/ADC10    |  P0.2/ADC10     |  P0.2/ADC10    |  N/A       |  P3.2/ADC10  |  P0.2/ADC10 |                     
|  1011 | P0.3/ADC11   |  P3.3/ADC11  |  P0.3/ADC11    |  P0.3/ADC11     |  P0.3/ADC11    |  N/A       |  P3.3/ADC11  |  P0.3/ADC11 |                     
|  1100 | N/A          |  P3.4/ADC12  |  P0.4/ADC12    |  P0.4/ADC12     |  P0.4/ADC12    |  N/A       |  P3.4/ADC12  |  P0.4/ADC12 |              
|  1101 | N/A          |  P3.5/ADC13  |  P0.5/ADC13    |  P0.5/ADC13     |  P0.5/ADC13    |  N/A       |  P3.5/ADC13  |  P0.5/ADC13 |              
|  1110 | N/A          |  P3.6/ADC14  |  P0.6/ADC14    |  P0.6/ADC14     |  P0.6/ADC14    |  N/A       |  P3.6/ADC14  |  P0.6/ADC14 |              
|  1111 | 1.19Vref     |  1.19Vref    |  1.19Vref      |  1.19Vref       |  1.19Vref      |  1.19Vref  |  1.19Vref    |  1.19Vref   |
