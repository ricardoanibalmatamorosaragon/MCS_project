list = dir('C:\Users\Histella\Downloads\mat');
for i = 3:9
load(append (list(i).folder,'\',list(i).name))
A=Problem.A;
n=size(A,1);
xe=ones(n,1);
b=A*xe;
tic;
x=A\b;
list_time(i)=toc;
norm(x-xe)/norm(xe)
[user,sys] = memory;
user.MemUsedMATLAB;
end
bar(list_time(1,3:end))

