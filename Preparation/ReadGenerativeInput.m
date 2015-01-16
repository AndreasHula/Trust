
Output = zeros(48,10);
Name=input('Please enter filename containing generative data: ', 's');
Long = input('Please input number of generated exchanges: ');
Were = input('Were Posteriors generated? (0 = no, 1 = yes): ');
Values = zeros(2*Long,10);
Beliefs = zeros(3,3,10,2*Long);
BeliefVariance=zeros(3,3,18);
IndividualProbability = zeros(3,3,10,2*Long);
fid = fopen([Name '.bin'],'r');
    for i = 1:Long
        for j = 1:10
           Values(2*(i-1)+1,j)= 1/4*fread(fid,1,'int32');
           Values(2*(i),j)=1/6*fread(fid,1,'int32');
        end
        if Were==1
            for j = 1:10
                for s = 1:3
                    for k = 1:3
                        Beliefs(s,k,j,2*(i-1)+1)=fread(fid,1,'double');
                    end
                end
            end
            for j = 1:10
                for s = 1:3
                   for k = 1:3
                         Beliefs(s,k,j,2*i)=fread(fid,1,'double');                   
                    end
                end
            end      
        end
    end
fclose(fid);

Output(1,:)=mean(Values(2*(1:Long)-1,:));
Output(2,:)=std(Values(2*(1:Long)-1,:));
Output(3,:)=mean(Values(2*(1:Long),:));
Output(4,:)=std(Values(2*(1:Long),:));
if(Were==1)
    for t = 1:10
        for k = 1:2*Long     
            IndividualProbability(:,1,t,k) = Beliefs(:,1,t,k)/sum(Beliefs(:,1,t,k));
            IndividualProbability(:,2,t,k) = Beliefs(:,2,t,k)/sum(Beliefs(:,2,t,k));
            IndividualProbability(:,3,t,k) = Beliefs(:,3,t,k)/sum(Beliefs(:,3,t,k));        
        end
    end
    Term = mean(Beliefs(:,:,9,2*(1:Long)-1),4);
    Output(13:15,1)=Term(:,1)/sum(Term(:,1));
    Output(13:15,2)=Term(:,2)/sum(Term(:,2));
    Output(13:15,3)=Term(:,3)/sum(Term(:,3));
    for i = 1:3
        for j = 1:3
            for k = 1:Long
                BeliefVariance(i,j,1) = BeliefVariance(i,j,1) + (IndividualProbability(i,j,9,2*k-1)- Output(12+i,j))^2;
            end
            BeliefVariance(i,j,1) = 1/(Long-1)*sqrt(BeliefVariance(i,j,1));    
       end
    end

    Term = mean(Beliefs(:,:,9,2*(1:Long)),4);
    Output(13:15,4)=Term(:,1)/sum(Term(:,1));
    Output(13:15,5)=Term(:,2)/sum(Term(:,2));
    Output(13:15,6)=Term(:,3)/sum(Term(:,3));
    for i = 1:3
        for j = 1:3
            for k = 1:Long
                BeliefVariance(i,j,2) = BeliefVariance(i,j,2) + (IndividualProbability(i,j,9,2*k)- Output(12+i,j+3))^2;
            end
            BeliefVariance(i,j,2) = 1/(Long-1)*sqrt(BeliefVariance(i,j,2));    
       end
    end

    Term = mean(Beliefs(:,:,6,2*(1:Long)-1),4);
    Output(16:18,1)=Term(:,1)/sum(Term(:,1));
    Output(16:18,2)=Term(:,2)/sum(Term(:,2));
    Output(16:18,3)=Term(:,3)/sum(Term(:,3));
    for i = 1:3
        for j = 1:3
            for k = 1:Long
                BeliefVariance(i,j,3) = BeliefVariance(i,j,3) + (IndividualProbability(i,j,6,2*k-1)- Output(15+i,j))^2;
            end
            BeliefVariance(i,j,3) = 1/(Long-1)*sqrt(BeliefVariance(i,j,3));    
       end
    end

    Term = mean(Beliefs(:,:,6,2*(1:Long)),4);
    Output(16:18,4)=Term(:,1)/sum(Term(:,1));
    Output(16:18,5)=Term(:,2)/sum(Term(:,2));
    Output(16:18,6)=Term(:,3)/sum(Term(:,3));
    for i = 1:3
        for j = 1:3
            for k = 1:Long
                BeliefVariance(i,j,4) = BeliefVariance(i,j,4) + (IndividualProbability(i,j,6,2*k)- Output(15+i,j+3))^2;
            end
            BeliefVariance(i,j,4) = 1/(Long-1)*sqrt(BeliefVariance(i,j,4));    
       end
    end

    Term = mean(Beliefs(:,:,3,2*(1:Long)-1),4);
    Output(19:21,1)=Term(:,1)/sum(Term(:,1));
    Output(19:21,2)=Term(:,2)/sum(Term(:,2));
    Output(19:21,3)=Term(:,3)/sum(Term(:,3));
    for i = 1:3
        for j = 1:3
            for k = 1:Long
                BeliefVariance(i,j,5) = BeliefVariance(i,j,5) + (IndividualProbability(i,j,3,2*k-1)- Output(18+i,j))^2;
            end
            BeliefVariance(i,j,5) = 1/(Long-1)*sqrt(BeliefVariance(i,j,5));    
       end
    end

    Term = mean(Beliefs(:,:,3,2*(1:Long)),4);
    Output(19:21,4)=Term(:,1)/sum(Term(:,1));
    Output(19:21,5)=Term(:,2)/sum(Term(:,2));
    Output(19:21,6)=Term(:,3)/sum(Term(:,3));
    for i = 1:3
        for j = 1:3
            for k = 1:Long
                BeliefVariance(i,j,6) = BeliefVariance(i,j,6) + (IndividualProbability(i,j,3,2*k)- Output(18+i,j+3))^2;
            end
            BeliefVariance(i,j,6) = 1/(Long-1)*sqrt(BeliefVariance(i,j,6));    
       end
    end

    for k = 1:6
        for i = 1:3
            for j = 1:3
                Output(21+k, 3*(i-1)+j)= BeliefVariance(i,j,k);
            end
        end
    end
end
 Gra=errorbar(transpose([Output(1,:);Output(3,:)]),transpose([Output(2,:);Output(4,:)]),'DisplayName','Output(1,:)', 'LineWidth', 3,'YDataSource','Output(1,:)');figure(gcf);
axis( [1 10 0 1] );
box off;
xlabel('Round Number', 'fontsize', 50, 'FontName', 'Times');
ylabel('Average Percentage sent', 'fontsize', 50, 'FontName', 'Times');
set(gca, 'YTick', [0 0.25 0.5 0.75 1]);
Graph = get(Gra, 'Child');
set(Graph{1,1}(2),'color',[0 0 0]);
set(Graph{2,1}(1),'color',[1 0 0]); 
set(Graph{2,1}(2),'color',[0 0 0]);
