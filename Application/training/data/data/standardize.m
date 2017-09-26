function [] = standardize()

    dataToPlot = zeros(0,87,0);
    
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
    end
    size(dataToPlot)
    dataToPlot = max(dataToPlot);
    C1 = permute(dataToPlot, [1 3 2]);
    C1 = reshape(C1,[],size(dataToPlot,2),1);
    c = ones(size(C1,1),1)*100000;
    finalData = [C1 c];
    

    dataToPlot = zeros(0,87,0);
    
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
    
     size(dataToPlot)
    dataToPlot = max(dataToPlot);
    C2 = permute(dataToPlot, [1 3 2]);
    C2 = reshape(C2,[],size(dataToPlot,2),1);
    c = ones(size(C2,1),1)*200000;
    finalData2 = [C2 c];
    

    dataToPlot = zeros(0,87,0);
    
    
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
    
     size(dataToPlot)
    dataToPlot = max(dataToPlot);
    C3 = permute(dataToPlot, [1 3 2]);
    C3 = reshape(C3,[],size(dataToPlot,2),1);
    c = ones(size(C3,1),1)*300000;
    finalData3 = [C3 c];
    

    dataToPlot = zeros(0,87,0);
    
    
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

     size(dataToPlot)
    dataToPlot = max(dataToPlot);
    C4 = permute(dataToPlot, [1 3 2]);
    C4 = reshape(C4,[],size(dataToPlot,2),1);
    c = ones(size(C4,1),1)*400000;
    finalData4 = [C4 c];
    

    dataToPlot = zeros(0,87,0);
    
    
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

     size(dataToPlot)
    dataToPlot = max(dataToPlot);
    C5 = permute(dataToPlot, [1 3 2]);
    C5 = reshape(C5,[],size(dataToPlot,2),1);
    c = ones(size(C5,1),1)*500000;
    finalData5 = [C5 c];
    

    fd = [finalData;finalData2;finalData3;finalData4;finalData5];
    
    fd = fd(:,4:end);
    size(fd)
    save('collatedData.mat','fd');

end