%Matlab Readout script by A. Hula - 8.Sept.2014
%Self Generated Accuracy and Running Time estimation readout.
Name=input('Please enter filename to contain parameter data: ', 's');
Condition = input('Please input condition chosen during generation (0 for table or 1 for converged): ');
if Condition==0
    Long = input('Please input number of generated exchanges: ');
    QValues = zeros(5,Long,8); %Action Probability
    QCovar = zeros(5,5,8); %Sample Covariances of initial action probabilities
    Time = zeros(Long, 8); %Calculation Time for First action
else
    QValues = zeros(5,8);
    Time = zeros(1,8);
end

if Condition== 0
fid = fopen([Name '.bin'],'r');   
    for k =1:8
        for i = 1:(Long)
            for s = 1:5
                QValues(s,i,  k)=fread(fid,1,'double');
            end        
            Time(i,  k) = fread(fid,1,'double');
        end
       % hold = fread(fid,1,'double');
    end
fclose(fid);
    QMean = zeros(5,8);

    for k =1:8
        for i =1 :5
            QMean(i, k) = mean(QValues(i,:,k));
        end
    end   
    CovarNorm = zeros(1,8);
    NormTime = zeros(1,8);

    for s =1:8
        for i = 1:5
            for j = 1:5
                QCovar(i,j, s) = 1/(Long-1)*sum((QValues(i,:, s)-QMean(i,s)).*(QValues(j,:, s)-QMean(j,s)));
            end
        end
        CovarNorm(s) = sum(sum(QCovar(:,:, s).^2));
        NormTime(s) = mean(Time(:,s));
    end
else
fid = fopen([Name '.bin'],'r');     
    for k = 1:8
        for s = 1:5
            QValues(s, k)=fread(fid,1,'double');
        end        
        Time(k) = fread(fid,1,'double');
    end
fclose(fid);    
end
