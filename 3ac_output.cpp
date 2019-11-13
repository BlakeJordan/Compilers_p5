#include "ast.hpp"

namespace lake{

IRProgram * ProgramNode::to3AC(){
	IRProgram * prog = new IRProgram();
	myDeclList->to3AC(prog);
	return prog;
}

//Process local scope variables
void VarDeclListNode::to3AC(Procedure * proc){
	for (auto decl : *myDecls){
		decl->to3AC(proc);
	}
}

//Process DeclList at the global scope
void DeclListNode::to3AC(IRProgram * prog){
	for (auto decl : *myDecls){
		decl->to3AC(prog);
	}
}

void FnDeclNode::to3AC(IRProgram * prog){
	TODO(Implement me)
}

void FnDeclNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void FormalDeclNode::to3AC(IRProgram * prog){
	TODO(Implement me)
}

void FormalDeclNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void FormalsListNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ExpListNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void StmtListNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void FnBodyNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

Opd * IntLitNode::flatten(Procedure * proc){
	return new LitOpd(std::to_string(myInt));
}

Opd * StrLitNode::flatten(Procedure * proc){
	Opd * res = proc->getProg()->makeString(myString);
	return res;
}

Opd * TrueNode::flatten(Procedure * prog){
	TODO(Implement me)
}

Opd * FalseNode::flatten(Procedure * prog){
	TODO(Implement me)
}

Opd * AssignNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * DerefNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * CallExpNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * UnaryMinusNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * NotNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * PlusNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * MinusNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * TimesNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * DivideNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * AndNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * OrNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * EqualsNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * NotEqualsNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * LessNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * GreaterNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * LessEqNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * GreaterEqNode::flatten(Procedure * proc){
	TODO(Implement me)
}

void AssignStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void PostIncStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void PostDecStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ReadStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void WriteStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void IfStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void IfElseStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void WhileStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void CallStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ReturnStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void VarDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = getDeclaredID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}
	proc->gatherLocal(sym);
}

void VarDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = getDeclaredID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}
	
	prog->gatherGlobal(sym);
}

//We only get to this node if we are in a stmt
// context (DeclNodes protect descent) 
Opd * IdNode::flatten(Procedure * proc){
	TODO(Implement me)
}


}
