Name=input('Please enter filename to contain parameter data: ', 's');
Long = input('Please input number of exchanges to be generated: ');
Validat = zeros(Long,6);
Validat(:,1) = input('Please input Investor Guilt (0, 1 or 2): ');
Validat(:,2) = input('Please input Investor Planning (0, 2 or 7): ');
Validat(:,3) = input('Please input Investor ToM (0 or 2): ');
Validat(:,4) = input('Please input Trustee Guilt (0, 1 or 2): ');
Validat(:,5) = input('Please input Trustee Planning (0, 2 or 7): ');
Validat(:,6) = input('Please input Trustee ToM (0 or 1): ');
fid =fopen([Name '.bin'],'w');
for i=1:Long
    for j =1:6
         fwrite(fid,cast(Validat(i,j),'int8'),'int32');    
    end
end
fclose(fid);
