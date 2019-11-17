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
		SemSymbol * mySym = myID->getSymbol();
		Procedure * proc = prog->makeProc(mySym->getName());
		myFormals->to3AC(proc);
		myBody->to3AC(proc);
		// TODO(Implement me)
	}

	void FnDeclNode::to3AC(Procedure * proc){
		// cant happen outside Mr. WorldWide
		TODO(Implement me)
	}

	void FormalDeclNode::to3AC(IRProgram * prog){
		// cant happen in Mr. WorldWide
		TODO(Implement me)
	}

	void FormalDeclNode::to3AC(Procedure * proc){
		SemSymbol * sym = this->myID->getSymbol();
		proc->gatherFormal(sym);
		//TODO(Implement me)
	}

	void FormalsListNode::to3AC(Procedure * proc){
		size_t argNum = 1;
		for (auto formal : *myFormals) {
			formal->to3AC(proc);
			SemSymbol * sym = formal->getDeclaredID()->getSymbol();
			SymOpd * opd = proc->getSymOpd(sym);
			Quad * inQuad = new GetInQuad(argNum, opd);
			proc->addQuad(inQuad);
			argNum += 1;
		}
		// TODO(Implement me)
	}

	void ExpListNode::to3AC(Procedure * proc){
		size_t expNum = 1;
		for (auto exp : *myExps) {
			Opd * expOpd = exp->flatten(proc);
			Quad * argQuad = new SetInQuad(expNum, expOpd);
			proc->addQuad(argQuad);
			expNum++;
		}
		// TODO(Implement me)
	}

	void StmtListNode::to3AC(Procedure * proc){
		for (auto stmt : *myStmts) {
			stmt->to3AC(proc);
		}
		// TODO(Implement me)
	}

	void FnBodyNode::to3AC(Procedure * proc){
		myVarDecls->to3AC(proc);
		myStmtList->to3AC(proc);
		// TODO(Implement me)
	}

	Opd * IntLitNode::flatten(Procedure * proc){
		return new LitOpd(std::to_string(myInt));
	}

	Opd * StrLitNode::flatten(Procedure * proc){
		return proc->getProg()->makeString(myString);
	}

	Opd * TrueNode::flatten(Procedure * proc){
		return new LitOpd("1");
		// TODO(Implement me)
	}

	Opd * FalseNode::flatten(Procedure * proc){
		return new LitOpd("0");
		// TODO(Implement me)
	}

	Opd * AssignNode::flatten(Procedure * proc){
		Opd * lhs = mySrc->flatten(proc);
		Opd * rhs = myTgt->flatten(proc);
		AssignQuad * assignQuad = new AssignQuad(rhs, lhs);
		proc->addQuad(assignQuad);
		return lhs;
		//TODO(Implement me)
	}

	Opd * DerefNode::flatten(Procedure * proc){
		Opd * src = myTgt->flatten(proc);
		Opd * tgt = proc->makeTmp();
		LocQuad * derefQuad = new LocQuad(src, tgt);
		proc->addQuad(derefQuad);
		return tgt;
		// TODO(Implement me)
	}

	Opd * CallExpNode::flatten(Procedure * proc){
		myExpList->to3AC(proc);
		CallQuad * farQuad = new CallQuad(myId->getSymbol());
		proc->addQuad(farQuad);
		SemSymbol * funcId = myId->getSymbol();
		auto * returnType = funcId->getType()->asFn();
		if (returnType->getReturnType()->isVoid()){
			return nullptr;
		} else {
			Opd * ret = proc->makeTmp();
			Quad * getOutQuad = new GetOutQuad(1, ret);
			proc->addQuad(getOutQuad);
			return ret;
		}
		// TODO(Implement me)
	}

	Opd * UnaryMinusNode::flatten(Procedure * proc){
		Opd * src = myExp->flatten(proc);
		Opd * dst = proc->makeTmp();
		Quad * negQuad = new UnaryOpQuad(dst, NEG, src);
		proc->addQuad(negQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * NotNode::flatten(Procedure * proc){
		Opd * src = myExp->flatten(proc);
		Opd * dst = proc->makeTmp();
		Quad * notQuad = new UnaryOpQuad(dst, NOT, src);
		proc->addQuad(notQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * PlusNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * plusQuad = new BinOpQuad(dst, ADD, lhs, rhs);
		proc->addQuad(plusQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * MinusNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * subQuad = new BinOpQuad(dst, SUB, lhs, rhs);
		proc->addQuad(subQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * TimesNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * multQuad = new BinOpQuad(dst, MULT, lhs, rhs);
		proc->addQuad(multQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * DivideNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * divQuad = new BinOpQuad(dst, DIV, lhs, rhs);
		proc->addQuad(divQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * AndNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * andQuad = new BinOpQuad(dst, AND, lhs, rhs);
		proc->addQuad(andQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * OrNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * orQuad = new BinOpQuad(dst, OR, lhs, rhs);
		proc->addQuad(orQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * EqualsNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * eQuad = new BinOpQuad(dst, EQ, lhs, rhs);
		proc->addQuad(eQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * NotEqualsNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * neQuad = new BinOpQuad(dst, NEQ, lhs, rhs);
		proc->addQuad(neQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * LessNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * ltQuad = new BinOpQuad(dst, LT, lhs, rhs);
		proc->addQuad(ltQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * GreaterNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * gtQuad = new BinOpQuad(dst, GT, lhs, rhs);
		proc->addQuad(gtQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * LessEqNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * leQuad = new BinOpQuad(dst, LTE, lhs, rhs);
		proc->addQuad(leQuad);
		return dst;
		// TODO(Implement me)
	}

	Opd * GreaterEqNode::flatten(Procedure * proc){
		Opd * lhs = myExp1->flatten(proc);
		Opd * rhs = myExp2->flatten(proc);
		Opd * dst = proc->makeTmp();
		BinOpQuad * gteQuad = new BinOpQuad(dst, GTE, lhs, rhs);
		proc->addQuad(gteQuad);
		return dst;
		// TODO(Implement me)
	}

	void AssignStmtNode::to3AC(Procedure * proc){
		myAssign->flatten(proc);
		// TODO(Implement me)
	}

	void PostIncStmtNode::to3AC(Procedure * proc){
		Opd * val = myExp->flatten(proc);
		BinOpQuad * incQuad = new BinOpQuad(val, ADD, val, new LitOpd("1"));
		proc->addQuad(incQuad);
		// TODO(Implement me)
	}

	void PostDecStmtNode::to3AC(Procedure * proc){
		Opd * val = myExp->flatten(proc);
		BinOpQuad * decQuad = new BinOpQuad(val, SUB, val, new LitOpd("1"));
		proc->addQuad(decQuad);
		// TODO(Implement me)
	}

	void ReadStmtNode::to3AC(Procedure * proc){
		Opd * stmt = myExp->flatten(proc);
		SyscallQuad * readQuad = new SyscallQuad(READ, stmt);
		proc->addQuad(readQuad);
 		// TODO(Implement me)
	}

	void WriteStmtNode::to3AC(Procedure * proc){
		Opd * stmt = myExp->flatten(proc);
		SyscallQuad * writeQuad = new SyscallQuad(WRITE, stmt);
		proc->addQuad(writeQuad);
		// TODO(Implement me)
	}

	void IfStmtNode::to3AC(Procedure * proc){
		Opd * boolExp = myExp->flatten(proc);
		Label * lbl_end = proc->makeLabel();
		NopQuad * end = new NopQuad();
		end->addLabel(lbl_end);
		JmpIfQuad * ifQuad = new JmpIfQuad(boolExp, false, lbl_end);
		proc->addQuad(ifQuad);
		myDecls->to3AC(proc);
		myStmts->to3AC(proc);
		proc->addQuad(end);
		// TODO(Implement me)
	}

	void IfElseStmtNode::to3AC(Procedure * proc){
		Label * lbl_ifFalse = proc->makeLabel();
		Quad * ifFalse = new NopQuad();
		ifFalse->addLabel(lbl_ifFalse);
		Label * lbl_end = proc->makeLabel();
		Quad * end = new NopQuad();
		end->addLabel(lbl_end);
		Opd * boolExp = myExp->flatten(proc);
		Quad * ifQuad = new JmpIfQuad(boolExp, false, lbl_ifFalse);
		proc->addQuad(ifQuad);
		myDeclsT->to3AC(proc);
		myStmtsT->to3AC(proc);
		Quad * elseQuad = new JmpQuad(lbl_end);
		proc->addQuad(elseQuad);
		proc->addQuad(ifFalse);
		myDeclsF->to3AC(proc);
		myStmtsF->to3AC(proc);
		proc->addQuad(end);
		// TODO(Implement me)
	}

	void WhileStmtNode::to3AC(Procedure * proc){
		Quad * head = new NopQuad();
		Label * lbl_head = proc->makeLabel();
		head->addLabel(lbl_head);
		Quad * end = new NopQuad();
		Label * lbl_end = proc->makeLabel();
		end->addLabel(lbl_end);
		proc->addQuad(head);
		Opd * boolExp = myExp->flatten(proc);
		Quad * ifFalseQuad = new JmpIfQuad(boolExp, false, lbl_end);
		proc->addQuad(ifFalseQuad);
		myDecls->to3AC(proc);
		myStmts->to3AC(proc);
		Quad * ifTrueQuad = new JmpQuad(lbl_head);
		proc->addQuad(ifTrueQuad);
		proc->addQuad(end);
		// TODO(Implement me)
	}

	void CallStmtNode::to3AC(Procedure * proc){
		Opd * returnVal = myCallExp->flatten(proc);
		if (returnVal != NULL) {
			proc->popQuad();
		}
		// TODO(Implement me)
	}

	void ReturnStmtNode::to3AC(Procedure * proc){
		if(myExp != NULL) {
			Opd * retVal = myExp->flatten(proc);
			Quad * returnQuad = new SetOutQuad(1, retVal);
			proc->addQuad(returnQuad);
		}
		Quad * exitJmp = new JmpQuad(proc->getLeaveLabel());
		proc->addQuad(exitJmp);
		// TODO(Implement me)
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
		// TODO(Implement me);
		return proc->getSymOpd(this->getSymbol());
	}
}
