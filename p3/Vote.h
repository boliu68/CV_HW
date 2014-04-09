#include"define.h"

class StickVote
{
public:
	Vec3d position;
	Vec3d direction;
	StickVote(const Vec3d &p);
};

class TensorVote:public StickVote
{
public:
	enum Type{BALL,STICK,PLATE};
private:
	Matx33d tensor;
	Matx33d tensorsum;//accumulate voting result
	Matx33d eigenVectors;
	double eigenValues[3];
	double saliency[3];
	//initial encoding of three types
	void InitialBall();
	void InitialStick(const Vec3d &normal);
	void InitialStick();
	void InitialPlate(const Vec3d &tangent);
	void InitialPlate();
	void InitialTensor();
	void Combine(const StickVote &sv,double weight);//combine voting to tensorsum
	StickVote genStickVote(const TensorVote &voter,double sigma,double c);
	//genenrate stick vote
	void combineTensorFromField(const TensorVote &voter,double sigma,const vector<vector<vector<Matx33d> > > &field);
	//combine tensor voting from precomputed voting field
	//void combineTensorFromField(const TensorVote &voter,double sigma,const vector<Matx33d> &field);
public:
	TensorVote(const Vec3d &p);
	TensorVote(const Vec3d &p,Type type,const Vec3d &normal);
	TensorVote(const Vec3d &p,Type type);
	void genTensorVote(const TensorVote &voter,double sigma,double c
		,const vector<Vec3d> &sphereSamples,const vector<Vec3d> &circleSamples);
	//Voting by sampling
	void genTensorVote(const TensorVote &voter,double sigma,
		const vector<vector<vector<Matx33d> > > &stickField,
		const vector<vector<vector<Matx33d> > > &plateField,
		const vector<vector<vector<Matx33d> > > &sphereField);
	//Voting by precomputed voting field
	void CloseFormVote(const TensorVote &voter,double sigma);
	//Voting by close-form without voting field
	double Interpretation(vector<Vec3d> &eigens);
	//Interpret voting result by eigenvectors*corresponding eigenvalue,
	//return sqrt(square sum of eigen values)
	Matx33d getOutTensor();
	void resetOutTensor();
};

class TensorVoting
{
private:
	vector<TensorVote> tensors;
	vector<Vec3d> sphereSamples;
	vector<Vec3d> circleSamples;
	void generateSphereSamples(int NSAMPLE);
	void generateCircleSamples(int NSAMPLE);
	void subdivideTriangle(const vector<Vec3d> &tri,int level);
	//subdivide one triangle in icosahedron to get 4^level samples
	double getBoundingBoxScale();//get bounding box scale of input data
	//store precomputed field
	vector<vector<vector<Matx33d> > > stickField;
	vector<vector<vector<Matx33d> > > plateField;
	vector<vector<vector<Matx33d> > > sphereField;
	double readFieldFile(const string &fname);
public:
	TensorVoting();
	void readFile(const string &fname,bool normal=true);
	void CloseFormVoting(double sigma);
	//tensor voting by close-form without voting field
	void VotingWithField(double sigma,double constant,double nsample);
	//tensor voting by sampling voting field
	void VotingWithField(const string &fname);
	//tensor voting by precomputed voting field
	void OutPut(const string &prefix,double thred);
	//out put view world files, thred is used to eliminate outliers whose saliency is less than thred*max saliency
	void generateFieldFile(const string &prefix,int K,double sigma,double constant,double nsample);
	//out put field file. K is field size
};