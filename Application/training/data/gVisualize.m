function [] = gVisualize (handles)

    userData = get(handles.selectAction,'Value');
    trialsFrom = str2num(get(handles.trialsFrom,'String'));
    trialsTo = str2num(get(handles.trialsTo,'String'));
    sensor = get(handles.sensorSelect,'Value');
    params = get(handles.dataSelect,'Value');
    
    switch userData
        case 1
            userData = 'Blink';
        case 2
            userData = 'Smile';
        case 3
            userData = 'Clench';
        case 4
            userData = 'Brow';
        case 5
            userData = 'Furrow';
    end
    
    switch sensor
        case 1
            sensor = 4;
            sensorName = 'AF3';
        case 2
            sensor = 10;
            sensorName = 'F7';
        case 3
            sensor = 16;
            sensorName = 'F3';
        case 4
            sensor = 22;
            sensorName = 'FC5';
        case 5
            sensor = 28;
            sensorName = 'T7';
        case 6
            sensor = 34;
            sensorName = 'P7';
        case 7
            sensor = 40;
            sensorName = 'O1';
        case 8
            sensor = 46;
            sensorName = 'O2';
        case 9
            sensor = 52;
            sensorName = 'P8';
        case 10
            sensor = 58;
            sensorName = 'T8';
        case 11
            sensor = 64;
            sensorName = 'FC6';
        case 12
            sensor = 70;
            sensorName = 'F4';
        case 13
            sensor = 76;
            sensorName = 'F8';
        case 14
            sensor = 82;
            sensorName = 'AF4';
    end
    
    dataToPlot = zeros(0,87,0);
%     userData = 'Smile';
    
    switch userData
        case 'Smile'
            disp('in smile');
            files = dir('smile*');
            fileIndex = find(~[files.isdir]);
            for i = 1:length(fileIndex)
                fileName = files(fileIndex(i)).name;
                load(fileName);
                x = size(dataToPlot);
                y = size(smileData);
                if (y(1) ~= 0)
                    if (x(1)>y(1))
                       smileData = padarray(smileData, [x(1)-y(1)], 0, 'post'); 
                    else
                        if (y(1)>x(1))
                            dataToPlot = padarray(dataToPlot, [y(1)-x(1)], 0, 'post');
                        end
                    end
                end
                dataToPlot = cat(3, dataToPlot, smileData);
                %dataToSend = smileData;
%                 size(dataToPlot)
            end

        case 'Clench'
            disp('in clench');
            files = dir('clench*');
            fileIndex = find(~[files.isdir]);
            for i = 1:length(fileIndex)
                fileName = files(fileIndex(i)).name;
                load(fileName);
                x = size(dataToPlot);
                y = size(clenchData);
                if (y(1) ~= 0)
                    if (x(1)>y(1))
                       clenchData = padarray(clenchData, [x(1)-y(1)], 0, 'post'); 
                    else
                        if (y(1)>x(1))
                            dataToPlot = padarray(dataToPlot, [y(1)-x(1)], 0, 'post');
                        end
                    end
                end
                dataToPlot = cat(3, dataToPlot, clenchData);
                %dataToSend = clenchData;
%                 size(dataToPlot)
            end

        case 'Furrow'
            disp('in furrow');
            files = dir('furrow*');
            fileIndex = find(~[files.isdir]);
            for i = 1:length(fileIndex)
                fileName = files(fileIndex(i)).name;
                load(fileName);
                x = size(dataToPlot);
                y = size(furrowData);
                if (y(1) ~= 0)
                    if (x(1)>y(1))
                       furrowData = padarray(furrowData, [x(1)-y(1)], 0, 'post'); 
                    else
                        if (y(1)>x(1))
                            dataToPlot = padarray(dataToPlot, [y(1)-x(1)], 0, 'post');
                        end
                    end
                end
                dataToPlot = cat(3, dataToPlot, furrowData);
                %dataToSend = furrowData;
%                 size(dataToPlot)
            end


        case 'Brow'
            disp('in brow');
            files = dir('brow*');
            fileIndex = find(~[files.isdir]);
            for i = 1:length(fileIndex)
                fileName = files(fileIndex(i)).name;
                load(fileName);
                x = size(dataToPlot);
                y = size(browData);
                if (y(1) ~= 0)
                    if (x(1)>y(1))
                       browData = padarray(browData, [x(1)-y(1)], 0, 'post'); 
                    else
                        if (y(1)>x(1))
                            dataToPlot = padarray(dataToPlot, [y(1)-x(1)], 0, 'post');
                        end
                    end
                end
                dataToPlot = cat(3, dataToPlot, browData);
                %dataToSend = browData;
%                 size(dataToPlot)
            end

        case 'Blink'
            disp('in blink');
            files = dir('blink*');
            fileIndex = find(~[files.isdir]);
            for i = 1:length(fileIndex)
                fileName = files(fileIndex(i)).name;
                load(fileName);
                x = size(dataToPlot);
                y = size(blinkData);
                if (y(1) ~= 0)
                    if (x(1)>y(1))
                       blinkData = padarray(blinkData, [x(1)-y(1)], 0, 'post'); 
                    else
                        if (y(1)>x(1))
                            dataToPlot = padarray(dataToPlot, [y(1)-x(1)], 0, 'post');
                        end
                    end
                end
                dataToPlot = cat(3, dataToPlot, blinkData);
                %dataToSend = blinkData;
%                 size(dataToPlot)
            end
    end

    if ((size(trialsFrom) == 0) & (size(trialsTo) == 0))
    elseif (size(trialsTo) == 0)
        dataToPlot = dataToPlot(:,:,trialsFrom:end);
    elseif (size(trialsFrom) == 0)
        dataToPlot = dataToPlot(:,:,end-trialsTo+1:end);
    else
        dataToPlot = dataToPlot(:,:,trialsFrom:trialsTo);
    end
    
    
%     size(dataToPlot)
    

    f = figure;
    p = uipanel('Parent',f,'BorderType','none'); 
    p.Title = strcat(sensorName,' - ',userData); 
    p.TitlePosition = 'centertop'; 
    p.FontSize = 12;
    p.FontWeight = 'bold';
    
    t = size(dataToPlot);
    t = 0:1:t(1) - 1;

    for i = 1:length(params)
        
        plotData = squeeze(dataToPlot(:,sensor+params(i)-1,:));
        factor = length(params);
        if (factor<=3)
            factor1 = 1;
            factor2 = factor;
        else
            factor1 = ceil(factor/3);
            factor2 = ceil(factor/2);
        end
        ax1 = subplot(factor2,factor1,i,'Parent', p);
        plot(ax1,t,plotData);
        maxY = ceil(max(max(plotData)));
        switch params(i)
            case 1
                plotName = 'Raw EEG';
                ylim([maxY-2000 maxY+10]);
            case 2
                plotName = 'Alpha';
            case 3
                plotName = 'Beta-Low';
            case 4
                plotName = 'Beta-High';
            case 5
                plotName = 'Theta';
                ylim([maxY-50000 maxY+10]);
            case 6
                plotName = 'Gamma';
        end
        
        title(ax1,plotName);
        xlabel(ax1,'samples');
        ylabel(ax1,'amplitude');
        
%         ylim([4000 4400])

    end
            
    
end