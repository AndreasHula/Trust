Name=input('Please enter filename containing estimation data: ', 's');
Long = input('Please input number of generated exchanges: ');
InvestorLikelihoods=zeros(1,Long); %Subject Wise
InvestorToM=zeros(1,Long); %Subject Wise
InvestorGuilt=zeros(1,Long); %Subject Wise
InvestorPlan=zeros(1,Long); %Subject Wise
TrusteeLikelihoods=zeros(1,Long); %Subject Wise
TrusteeToM=zeros(1,Long); %Subject Wise
TrusteeGuilt=zeros(1,Long); %Subject Wise
TrusteePlan=zeros(1,Long); %Subject Wise
InvestorBelief=zeros(3,3,10,Long); %Beliefs Subject Wise for every time
                                 %Parameters: (ToM level, Believed Guilt,
                                 %time step, subject number)
TrusteeBelief=zeros(3,3,10,Long); %Beliefs Subject Wise for every time
                                 %Parameters: (ToM level, Believed Guilt,
                                 %time step, subject number)  
fid =fopen([Name '.bin'], 'r');
for j = 1:Long
    InvestorLikelihoods(1,j)=fread(fid,1,'double');
    InvestorToM(1,j)=fread(fid,1,'int32');
    InvestorGuilt(1,j)=fread(fid,1,'int32');
    InvestorPlan(1,j)=fread(fid,1,'int32');
    TrusteeLikelihoods(1,j)=fread(fid,1,'double');
    TrusteeToM(1,j)=fread(fid,1,'int32');
    TrusteeGuilt(1,j)=fread(fid,1,'int32');
    TrusteePlan(1,j)=fread(fid,1,'int32');
    for t = 1:10
        for s=1:3
            for g =1:3
                InvestorBelief(s,g,t,j)=fread(fid,1,'double');
            end
        end
    end
    for t = 1:10
        for s=1:3
            for g =1:3
                TrusteeBelief(s,g,t,j)=fread(fid,1,'double');
            end
        end
    end   
end
fclose(fid);
