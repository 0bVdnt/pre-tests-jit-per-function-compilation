#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>

// Parse an LLVM IR module and print a compact function inventory.
// The listing includes declaration/definition kind and signature details.
int FuncLister(const char *progName, const char *module) {
  llvm::LLVMContext Context;
  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> M = llvm::parseIRFile(module, Err, Context);

  if (!M) {
    // Use LLVM's diagnostic output for malformed or missing input files.
    Err.print(progName, llvm::errs());
    return 1;
  }

  llvm::outs() << "Functions found in module '" << M->getModuleIdentifier()
               << "':\n";
  for (const auto &F : M->functions()) {
    llvm::outs() << (F.isDeclaration() ? " [decl] " : " [def] ");

    // Print canonical function signature: return type, symbol, and parameters.
    F.getReturnType()->print(llvm::outs());
    llvm::outs() << " @";
    if (F.hasName())
      llvm::outs() << F.getName();
    else
      llvm::outs() << "<anonymous>";
    llvm::outs() << "(";

    bool FirstArg = true;
    for (const auto &Arg : F.args()) {
      if (!FirstArg)
        llvm::outs() << ", ";
      Arg.getType()->print(llvm::outs());
      if (Arg.hasName())
        llvm::outs() << " %" << Arg.getName();
      FirstArg = false;
    }

    if (F.isVarArg()) {
      if (!FirstArg)
        llvm::outs() << ", ";
      llvm::outs() << "...";
    }
    llvm::outs() << ")\n";
  }
  return 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    llvm::errs() << "Usage: " << argv[0] << " <input.ll>\n";
    return 1;
  }
  return FuncLister(argv[0], argv[1]);
}
