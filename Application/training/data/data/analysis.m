clc;clear;
disp('start');

load('collatedData_filtered');

% AF3=cat(2,fd(:,1:6),fd(:,end)./100000);
% F7=cat(2,fd(:,7:12),fd(:,end)./100000);
% F3=cat(2,fd(:,13:18),fd(:,end)./100000);
% FC5=cat(2,fd(:,19:24),fd(:,end)./100000);
% T7=cat(2,fd(:,25:30),fd(:,end)./100000);
% P7=cat(2,fd(:,31:36),fd(:,end)./100000);
% O1=cat(2,fd(:,37:42),fd(:,end)./100000);
% O2=cat(2,fd(:,43:48),fd(:,end)./100000);
% P8=cat(2,fd(:,49:54),fd(:,end)./100000);
% T8=cat(2,fd(:,55:60),fd(:,end)./100000);
% FC6=cat(2,fd(:,61:66),fd(:,end)./100000);
% F4=cat(2,fd(:,67:72),fd(:,end)./100000);
% F8=cat(2,fd(:,73:78),fd(:,end)./100000);
% AF4=cat(2,fd(:,79:84),fd(:,end)./100000);

AF3=fd(:,1:6);
F7=fd(:,7:12);
F3=fd(:,13:18);
FC5=fd(:,19:24);
T7=fd(:,25:30);
P7=fd(:,31:36);
O1=fd(:,37:42);
O2=fd(:,43:48);
P8=fd(:,49:54);
T8=fd(:,55:60);
FC6=fd(:,61:66);
F4=fd(:,67:72);
F8=fd(:,73:78);
AF4=fd(:,79:84);

actions=fd(:,end)./100000;

s1='AF3';s2='F7';s3='F3';s4='FC5';s5='T7';s6='P7';
s7='O1';s8='O2';s9='P8';s10='T8';s11='FC6';s12='F4';s13='F8';s14='AF4';
ids=['s1' 's2' 's3' 's4' 's5' 's6' 's7' 's8' 's9' 's10' 's11' 's12' 's13' 's14'];
ids_num=[1:14];
sensors_w_id=struct(char(ids(1)),AF3(:,1:6),char(ids(2)),F7(:,1:6),char(ids(3)),F3(:,1:6),...
    char(ids(4)),FC5(:,1:6),char(ids(5)),T7(:,1:6),char(ids(6)),P7(:,1:6),...
    char(ids(7)),O1(:,1:6),char(ids(8)),O2(:,1:6),char(ids(9)),P8(:,1:6),...
    char(ids(10)),T8(:,1:6),char(ids(11)),FC6(:,1:6),char(ids(12)),F4(:,1:6),...
    char(ids(13)),F8(:,1:6),char(ids(14)),AF4(:,1:6));

sensors_w_name=struct(s1,AF3(:,1:6),s2,F7(:,1:6),s3,F3(:,1:6),s4,FC5(:,1:6)...
    ,s5,T7(:,1:6),s6,P7(:,1:6),s7,O1(:,1:6),s8,O2(:,1:6)...
    ,s9,P8(:,1:6),s10,T8(:,1:6),s11,FC6(:,1:6),s12,F4(:,1:6)...
    ,s13,F8(:,1:6),s14,AF4(:,1:6));

sensor_id_2_name=struct(char(ids(1)),'AF3',char(ids(2)),'F7',char(ids(3)),'F3',...
    char(ids(4)),'FC5',char(ids(5)),'T7',char(ids(6)),'P7',char(ids(7)),'O1',...
    char(ids(8)),'O2',char(ids(9)),'P8',char(ids(10)),'T8',char(ids(11)),'FC6',...
    char(ids(12)),'F4',char(ids(13)),'F8',char(ids(14)),'AF4');

clear s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14;
clear AF3 F7 F3 FC5 T7 P7 O1 O2 P8 T8 FC6 F4 F8 AF4 fd;


handles.sensors_w_id=sensors_w_id;
handles.ids=ids;
handles.actions=actions;

% calc s1,s3,s12,s14 first


clustering_analysis([1 3 12 14],handles);
clustering_analysis([1:14],handles);



%{
   for all clustering, we analyze both euclidean square distance and
   cityblock(a.k.a manhattan) distance to observe the datas. From initial
   observation, euclidean square distance leads to better clustering
   results and matching rates
%}
function clustering_analysis(sensor_ids,handles)
sensors_w_id=handles.sensors_w_id;
ids=handles.ids;
actions=handles.actions;
%{
%%%%%%%% Analysis by Each band%%%%%%%%%%%%%%%
based on the given sensors, analysis each signal bands through clustering
%}
% single band, from 1 to 6 is EEG, Alpha, Beta-low, Beta-high, Theta, Gamma
clusters_c=[];
clusters_eusq=[];
euclidean_sq_silhouette_mean=[];
city_silhouette_mean=[];
data=[];
for band = 1:6
    data=[];
    for sensor=1:size(sensor_ids)
        tmp=getfield(sensors_w_id,char(ids(sensor_ids(sensor))));
        data=[data, normalize(tmp(:,band))];
    end
%     data=[normalize(t1(:,band)),normalize(t2(:,band)),normalize(t3(:,band)),normalize(t4(:,band))];
    idx_c=kmeans(data,5,'Distance','cityblock');
    idx_eusq=kmeans(data,5);
    clusters_c=[clusters_c,idx_c];
    clusters_eusq=[clusters_eusq,idx_eusq];
%     figure;
    [sil_c,h]=silhouette(data,idx_c,'cityblock');
%     figure;
    [sil_eusq,h]=silhouette(data,idx_eusq,'sqEuclidean');
    city_silhouette_mean=[city_silhouette_mean,mean(sil_c)];
    euclidean_sq_silhouette_mean=[euclidean_sq_silhouette_mean,mean(sil_eusq)];
end
clear data idx_c idx_eusq band;


%{
%%%%%%%% analysis clusters matching rate%%%%%%%%%%%%%%%

TODO: not data seems not good for this
Problem: the clustering data is acceptable from the clustering perspective.
However, most of the time, one or two huge clusters will dominante across
all 5 categories. I'm still trying to find a visual/numeric ways to
represent this result.

based on the previous clustering results, analyze how much the pure
clustering by signals match their predefined categories.
the closer to zero, means the entries from this categories contains smaller
clusters, bad clustering. Go through one, means most of the entries from 
the original categories falls in one large cluster, which is a good result.
%}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%  analysis by cluster
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% [c ia ic]=unique(actions); % get unique value index of actions
% ia(end+1)=size(actions,1);
% 
% clusters_c_match_rates_by_band=[];
% clusters_eusq_match_rates_by_band=[];
% range_c=unique(actions);
% range_c=[range_c,range_c,range_c,range_c,range_c,range_c];
% range_eusq=range_c;
% 
% for idx=2:size(ia)
%     rate_action_c = [];
%     rate_action_eusq = [];
%     for band=1:6
%         total=ia(idx)-ia(idx-1);
%         [M,count_c]=mode_in_range(clusters_c(ia(idx-1):ia(idx)-1,band),range_c(:,band));
%         range_c(range_c(:,band)==M,band)=range_c(range_c(:,band)==M,band).*-1;
%         [M,count_eusq]=mode_in_range(clusters_eusq(ia(idx-1):ia(idx)-1,band),range_eusq(:,band));
%         range_eusq(range_eusq(:,band)==M,band)=range_eusq(range_eusq(:,band)==M,band).*-1;
%         rate_action_c=[rate_action_c,count_c/total]; % rate of every band/action
%         rate_action_eusq=[rate_action_eusq,count_eusq/total];
%     end
%     clusters_c_match_rates_by_band=[clusters_c_match_rates_by_band;rate_action_c]; % concat rates of every actions(vertical)
%     clusters_eusq_match_rates_by_band=[clusters_eusq_match_rates_by_band;rate_action_eusq];
% end
% clear idx rate_action_c rate_action_eusq c ia ic M h band total count_c count_eusq;
% 
% disp('end');
% 
end

function [M,F]=mode_in_range(data,range)
    M=0;
    F=0;
    while ~ismember(M,range)
        data=data(data~=M);
        [M,F]=mode(data);
    end
end

function normalized_data = normalize(data)
    normalized_data=data./max(abs(data));
end
