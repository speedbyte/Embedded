function drawBox ( roll, pitch,yaw, objID)
	coder.extrinsic('patch');
	coder.extrinsic('set');

	persistent figureArray patchArray crossArray;

	x1 = [-2 -2 2 2 -2]; 
	y1 = [-4 4 4 -4 -4]; 
	z1 = [0 0 0 0 0 ]; 

	xx = [0 1]; 
	yx = [0 0]; 
	zx = [0 0];

	xy = [0 0]; 
	yy = [0 1]; 
	zy = [0 0];

	xz = [0 0]; 
	yz = [0 0]; 
	zz = [0 1];

	if isempty(figureArray)
			objIDMax=3;
			figureArray=zeros(objIDMax,1);
			figureArray(objID) = figure;
			
			patchArray=zeros(objIDMax,1);
			patchArray(objID) = patch(x1, y1, z1,'r');

			crossArray = zeros(objIDMax,3);
			hold on
			crossArray(objID,1) = plot3(xx,yx,zx,'k','LineWidth',2); %x
			crossArray(objID,2) = plot3(xy,yy,zy,'k','LineWidth',2); %y
			crossArray(objID,3) = plot3(zx,zy,zz,'k','LineWidth',2); %z
					
			xlabel('x'); ylabel('y'); zlabel('z');
			if (objID == 1)
					title('Raw gyro sensors (integrated)');
			else
					title('Filtered (RPi output)');
			end
			grid
			axis([-7 7 -7 7 -7 7])
			view([45 15])
	end

	Rroll = [1,          0,           0;
					 0, cosd(roll), -sind(roll);
					 0, sind(roll), cosd(roll)];
					
	Rpitch = [cosd(pitch), 0, sind(pitch);
					 0,            1,           0;
					 -sind(pitch), 0, cosd(pitch)];
					
	Ryaw = [ cosd(yaw), -sind(yaw),  0;
					 sind(yaw),  cosd(yaw),  0;
					         0,          0,  1];

	xRot=zeros(size(x1));
	yRot=zeros(size(y1));
	zRot=zeros(size(z1));
	for i=1:length(xRot)
			temp=Rroll*Rpitch*Ryaw*[x1(i);y1(i);z1(i)];
			xRot(i)=temp(1);
			yRot(i)=temp(2);
			zRot(i)=temp(3);
	end

	xxRot=zeros(size(xx));
	yxRot=zeros(size(yx));
	zxRot=zeros(size(zx));
	for i=1:length(xxRot)
			temp=Rroll*Rpitch*Ryaw*[xx(i);yx(i);zx(i)];
			xxRot(i)=temp(1);
			yxRot(i)=temp(2);
			zxRot(i)=temp(3);
	end
	set(crossArray( objID,1), 'XData', xxRot);
	set(crossArray( objID,1), 'YData', yxRot);
	set(crossArray( objID,1), 'ZData', zxRot);

	xyRot=zeros(size(xy));
	yyRot=zeros(size(yy));
	zyRot=zeros(size(zy));
	for i=1:length(xyRot)
			temp=Rroll*Rpitch*Ryaw*[xy(i);yy(i);zy(i)];
			xyRot(i)=temp(1);
			yyRot(i)=temp(2);
			zyRot(i)=temp(3);
	end
	set(crossArray( objID,2), 'XData', xyRot);
	set(crossArray( objID,2), 'YData', yyRot);
	set(crossArray( objID,2), 'ZData', zyRot);


	xzRot=zeros(size(xz));
	yzRot=zeros(size(yz));
	zzRot=zeros(size(zz));
	for i=1:length(xzRot)
			temp=Rroll*Rpitch*Ryaw*[xz(i);yz(i);zz(i)];
			xzRot(i)=temp(1);
			yzRot(i)=temp(2);
			zzRot(i)=temp(3);
	end
	set(crossArray( objID,3), 'XData', xzRot);
	set(crossArray( objID,3), 'YData', yzRot);
	set(crossArray( objID,3), 'ZData', zzRot);


	set(patchArray( objID ),'XData', xRot);
	set(patchArray( objID ),'YData', yRot);
	set(patchArray( objID ),'ZData', zRot);
	drawnow
end


