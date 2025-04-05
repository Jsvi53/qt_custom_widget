clc;
clear;

%% 1. 数据加载与处理
% 文件路径
path = 'F:\code\projects\29_QT_projects\custom_widget\database\CRWU\12k Drive End Bearing Fault Data\Outer Race\Orthogonal\0007\144.mat';

% 加载数据
data = load(path);

% 采样频率（根据文件夹信息推断为12kHz）
Fs = 12000; 

% 构建时间轴
N = length(data.X144_BA_time);  % 假设三个通道长度相同
t = (0:N-1) / Fs;  % 时间轴（单位：秒）

%% 2. 绘图
% 绘制 X144_BA_time、X144_DE_time 和 X144_FE_time
figure;

subplot(3,1,1);
plot(t, data.X144_BA_time, 'r');
title('X144\_BA\_time');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(3,1,2);
plot(t, data.X144_DE_time, 'g');
title('X144\_DE\_time');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(3,1,3);
plot(t, data.X144_FE_time, 'b');
title('X144\_FE\_time');
xlabel('Time (s)');
ylabel('Amplitude');

%% 3. 保存数据为 CSV 文件
% 将数据转换成表格
t = table(data.X144_BA_time, data.X144_DE_time, data.X144_FE_time);

% 设置实际的列标题
t.Properties.VariableNames = {'X144_BA_time', 'X144_DE_time', 'X144_FE_time'};

% 保存为 CSV 文件
writetable(t, '../database\CRWU\12k Drive End Bearing Fault Data\Outer Race\Orthogonal\0007\144.csv');

%% 4. 打开 CSV 文件

clc;
clear;

% 文件路径
csv_file_path = '../database\CRWU\12k Drive End Bearing Fault Data\Outer Race\Orthogonal\0007\144.csv';

% 打开 CSV 文件
open(csv_file_path);
