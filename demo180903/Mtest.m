clc
clear
load net;
load data.mat;
string=input_data(1:end);
col=size(string,2);
ch1=string(1:8:col);
ch2=string(2:8:col);
ch3=string(3:8:col);
ch4=string(4:8:col);
ch5=string(5:8:col);
ch6=string(6:8:col);
ch7=string(7:8:col);
ch8=string(8:8:col);
str1=[ch1',ch2'];
str2=[ch3',ch4'];
str3=[ch5',ch6'];
str4=[ch7',ch8'];
col1=hex2dec(str1);
col2=hex2dec(str2);
col3=hex2dec(str3);
col4=hex2dec(str4);
testdata=[col1 col2 col3 col4];

meandata=mean(testdata);
input=meandata';
y=sim(net,input);

for i=1:3
    if y(i)>=0.5
        y(i)=1;
    else
        y(i)=0;
    end
end
y=y';
if y==[0 0 1]
    kind='0x01';
elseif y==[0 1 0]
    kind='0x02';
elseif y==[1 0 0]
    kind='0x03';
else
    kind='0x00';
end
if meandata==[0 0 0 0]
    kind='0x00';
end
if kind=='0x01'
    if meandata(3)>=0 && meandata(3)<10
        level='0x01';
    elseif meandata(3)>=10 && meandata(3)<20
        level='0x02';
    elseif meandata(3)>=20 && meandata(3)<30
        level='0x03';
    elseif meandata(3)>=30 && meandata(3)<40
        level='0x04';
    else
        level='0x05';
    end
elseif kind=='0x02'
    if meandata(3)>=0 && meandata(3)<3
        level='0x01';
    elseif meandata(3)>=3 && meandata(3)<6
        level='0x02';
    elseif meandata(3)>=6 && meandata(3)<9
        level='0x03';
    elseif meandata(3)>=9 && meandata(3)<12
        level='0x04';
    else
        level='0x05';
    end
elseif kind=='0x03'
    if meandata(3)>=0 && meandata(3)<3
        level='0x01';
    elseif meandata(3)>=3 && meandata(3)<6
        level='0x02';
    elseif meandata(3)>=6 && meandata(3)<9
        level='0x03';
    elseif meandata(3)>=9 && meandata(3)<12
        level='0x04';
    else
        level='0x05';
    end
elseif kind=='0x00'
        if meandata(3)>=0 && meandata(3)<3
        level='0x01';
    elseif meandata(3)>=3 && meandata(3)<6
        level='0x02';
    elseif meandata(3)>=6 && meandata(3)<9
        level='0x03';
    elseif meandata(3)>=9 && meandata(3)<12
        level='0x04';
    else
        level='0x05';
end
end
kind
level

