function  outPutVWFile(inprefix,outprefix)
slant=load(strcat(inprefix,'_slant.txt'));
tilt=load(strcat(inprefix,'_tilt.txt'));
nx=load(strcat(inprefix,'_x.txt'));
ny=load(strcat(inprefix,'_y.txt'));
nz=load(strcat(inprefix,'_z.txt'));
figure
needleplotst(slant, tilt,5, 2)
z= shapeletsurf(slant, tilt,6,1,2,'tiltamb');
%[dzdx, dzdy] = slanttilt2grad(slant, tilt);
%z = frankotchellappa(dzdx,dzdy);
z=z';
[h,w]=size(z);
% zmean=mean(z(:))*ones(h,w);
% zmax=max(z(:))*ones(h,w);
% zmin=min(z(:))*ones(h,w);
% z=z.*(abs(z-zmean)<=0.3*(zmax-zmin))+zmean.*(abs(z-zmean)>0.3*(zmax-zmin));
zmax=max(z(:));
zmin=min(z(:));
scale=norm([h w])/5/(zmax-zmin);
z=z*scale;
figure
surf(z);
axis ij;

s=(-nx+ny+nz)/sqrt(3);
s=s';
% smax=max(s(:));
% smin=min(s(:));
% s=(s-smin)/(smax-smin);
figure;
imshow(s);
imwrite(s,strcat(outprefix,'.bmp'));

fid=fopen(strcat(outprefix,'.vw'),'w');
for y=1:h-1
    for x=1:w-1
        %         fprintf(fid,'%f %f %f 4 %f %f\n', x,y,z(y,x),(x-1)/w,(y-1)/h);
        %         fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y,z(y,x+1),x/w,(y-1)/h);
        %         fprintf(fid,'%f %f %f 4 %f %f\n', x,y+1,z(y+1,x),(x-1)/w,y/h);
        %         fprintf(fid,'%f %f %f 4 %f %f\n', x,y+1,z(y+1,x),(x-1)/w,y/h);
        %         fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y+1,z(y+1,x+1),x/w,y/h);
        %         fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y,z(y,x+1),x/w,(y-1)/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x,y,z(h-y+1,x),(x-1)/w,1-(y-1)/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y,z(h-y+1,x+1),x/w,1-(y-1)/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x,y+1,z(h-y,x),(x-1)/w,1-y/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x,y+1,z(h-y,x),(x-1)/w,1-y/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y+1,z(h-y,x+1),x/w,1-y/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y,z(h-y+1,x+1),x/w,1-(y-1)/h);
    end
end
fclose(fid);
end