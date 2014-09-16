
Output = zeros(48,10);
Name=input('Please enter filename containing generative data: ', 's');
Long = input('Please input number of generated exchanges: ');
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
    end
fclose(fid);

Output(1,:)=mean(Values(2*(1:Long)-1,:));
Output(2,:)=std(Values(2*(1:Long)-1,:));
Output(3,:)=mean(Values(2*(1:Long),:));
Output(4,:)=std(Values(2*(1:Long),:));

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
