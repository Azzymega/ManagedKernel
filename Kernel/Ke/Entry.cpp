#include "Entry.hpp"

#include "Kernel/Reflector/Reflector.h"
#include "bcl.h"
#include "Kernel/October/Loader.h"
#include "Kernel/October/Linker.h"
#include "Kernel/Runtime/Engine.h"

World* Pointer;

Vector* Conveyor;
Vector* Definitions;

void Entry() {

    println("Initializing runtime!");

    Pointer->Register();

    Archiver Zipper = Archiver();
    Loader October = Loader();
    Linker Connect = Linker();

    Conveyor = Pointer->Vector(10);

    Vector* ClassFiles = Zipper.Load((void *) target_EBCL_0_5_jar, target_EBCL_0_5_jar_size);
    Definitions = Pointer->Vector(200);

    for (int i = 0; i < ClassFiles->Count; ++i) {
        auto* File = static_cast<RandomAccessFile *>(ClassFiles->Get(i));

        Definitions->Add(October.Load(File->Data->Bytes));
    }

    Connect.Link(Definitions);

    Task* Entry = Pointer->Task();

    Conveyor->Add(Entry);

    Entry->Stack = Pointer->Stack(15);
    Entry->Registers = Pointer->List(15);

    Entry->Registers->Set(1,Definitions);
    Entry->Registers->Set(0,Conveyor);

    Task* MainEntry = Pointer->Task();

    Conveyor->Add(MainEntry);

    MainEntry->Stack = Pointer->Stack(15);
    MainEntry->Registers = Pointer->List(15);

    Class* EntryClass = nullptr;

    for (int i = 0; i < Definitions->Count; ++i) {
        Class* Target = static_cast<Class *>(Definitions->Get(i));

        if (Target->Name->Equals("marx/base/BRVR")) {
            EntryClass = Target;
        }
    }

    Method* EntryPointMethod = nullptr;
    Method* InterruptRouter = nullptr;
    Method* MainMethod = nullptr;

    if (EntryClass == nullptr) {
        println("Failed to resolve MarxVM entry class!");
        return;
    }

    Executive::BRVR = EntryClass;

    for (int i = 0; i < EntryClass->Methods->Length; ++i) {
        auto* findTarget = static_cast<Method *>(EntryClass->Methods->GetObject(i));

        if (findTarget->Name->Equals("Start")) {
            EntryPointMethod = findTarget;
        }
        else if (findTarget->Name->Equals("Route")) {
            InterruptRouter = findTarget;
        }
        else if (findTarget->Name->Equals("Main")) {
            MainMethod = findTarget;
        }
    }

    if (EntryPointMethod == nullptr || InterruptRouter == nullptr || MainMethod == nullptr) {
        println("Failed to resolve MarxVM base methods!");
        return;
    }

    Executive::Route = InterruptRouter;

    Entry->Link = EntryClass;
    Entry->Instructions = EntryPointMethod->Instructions;

    MainEntry->Link = EntryClass;
    MainEntry->Instructions = MainMethod->Instructions;

    Executive::CriticalExecute(Entry);

    println("Executing finished!");

    Executive::Execute(MainEntry);
}