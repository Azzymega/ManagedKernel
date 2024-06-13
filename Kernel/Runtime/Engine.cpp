#include "Engine.h"

extern World* Pointer;
extern Vector* Definitions;
extern Vector* Conveyor;

void Executive::CriticalExecute(Task *task) {
    // fixme
    Executive::Interrupted = true;
    Executive::Execute(task);
    Executive::Interrupted = false;
}

void Executive::Execute(Task* Current) {

    for (; Current->Counter < Current->Instructions->Bytecode->Length; Current->Counter++) {

        CriticalStart();

        u1 Opcode = Current->Instructions->Bytecode->GetByte(Current->Counter);

        printf("Emitting opcode: ");
        printf(opcodesValues[Opcode]);
        println("");

        switch (Opcode) {

            case op_sipush: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = (FirstIndexByte << 8) | SecondIndexByte;

                Integer* Value = Pointer->Integer(IndexByte);

                Current->Stack->Push(Value);

                break;

            }

            case op_bipush: {

                u1 Byte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Integer* Value = Pointer->Integer(Byte);

                Current->Stack->Push(Value);

                break;

            }

            case op_aaload: {

                Integer* ArrayElementIndex = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = (Array*)(Current->Stack->TopAndPop());

                Object* Element = ArrayReference->GetObject(ArrayElementIndex->Value);

                Current->Stack->Push(Element);

                break;
            }

            case op_aastore: {

                Object* ArrayElementNewItem = Current->Stack->TopAndPop();
                Integer* ArrayElementIndex = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = (Array*)Current->Stack->TopAndPop();

                ArrayReference->Set(ArrayElementIndex->Value,ArrayElementNewItem);

                break;

            }

            case op_swap: {

                Object* First = Current->Stack->TopAndPop();
                Object* Second = Current->Stack->TopAndPop();

                Current->Stack->Push(Second);
                Current->Stack->Push(First);

                break;

            }

            case op_wide: {

                kassert(true, "[Executive] Wide opcode not implemented yet!");

                break;
            }

            case op_tableswitch: {

                kassert(true, "[Executive] Switch not implemented yet!");

                break;
            }

            case op_aconst_null: {

                Current->Stack->Push(nullptr);

                break;
            }

            case op_aload: case op_dload: case op_fload: case op_iload: case op_lload: {

                u1 Index = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Current->Stack->Push(Current->Registers->GetObject(Index));

                break;
            }

            case op_aload_0: case op_dload_0: case op_fload_0: case op_iload_0: case op_lload_0: {

                Current->Stack->Push(Current->Registers->GetObject(0));

                printf("Pushing to stack address ");
                printInteger((uintptr_t)Current->Stack->Top());
                printf(" from register ");
                printInteger(0);
                println("");

                break;
            }

            case op_aload_1: case op_dload_1: case op_fload_1: case op_iload_1: case op_lload_1: {

                Current->Stack->Push(Current->Registers->GetObject(1));

                printf("Pushing to stack address ");
                printInteger((uintptr_t)Current->Stack->Top());
                printf(" from register ");
                printInteger(1);
                println("");

                break;
            }

            case op_aload_2: case op_dload_2: case op_fload_2: case op_iload_2: case op_lload_2: {

                Current->Stack->Push(Current->Registers->GetObject(2));

                printf("Pushing to stack address ");
                printInteger((uintptr_t)Current->Stack->Top());
                printf(" from register ");
                printInteger(2);
                println("");

                break;
            }

            case op_aload_3: case op_dload_3: case op_fload_3: case op_iload_3: case op_lload_3: {

                Current->Stack->Push(Current->Registers->GetObject(3));

                printf("Pushing to stack address ");
                printInteger((uintptr_t)Current->Stack->Top());
                printf(" from register ");
                printInteger(3);
                println("");

                break;
            }

            case op_anewarray: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = (FirstIndexByte << 8) | SecondIndexByte;

                Integer* ArrayLength = static_cast<Integer *>(Current->Stack->TopAndPop());

                Current->Stack->Push((Object*)Pointer->List(ArrayLength->Value));

                break;
            }

            case op_return: {

                Task* PreviousTask = (Task*)Current->Stack->TopAndPop();

                if (!PreviousTask) {
                    return;
                }

                printf("Returning to method: ");
                PreviousTask->Instructions->Owner->Owner->Name->Log();
                printf(".");
                PreviousTask->Instructions->Owner->Name->Log();
                printf("::");
                PreviousTask->Instructions->Owner->Signature->Log();
                println("");

                Current->Switched = true;

                Current = PreviousTask;

                break;
            }

            case op_areturn: case op_dreturn: case op_freturn: case op_ireturn: case op_lreturn: {

                Object* Result = Current->Stack->TopAndPop();
                Task* PreviousTask = static_cast<Task *>(Current->Stack->TopAndPop());

                if (Result->Native == NativeType::NInteger) {
                    printf("Returning integer value: ");
                    printInteger(((Integer*)Result)->Value);
                    println("");
                }

                printf("Returning to method: ");
                PreviousTask->Instructions->Owner->Owner->Name->Log();
                printf(".");
                PreviousTask->Instructions->Owner->Name->Log();
                printf("::");
                PreviousTask->Instructions->Owner->Signature->Log();
                println("");

                Current->Switched = true;

                Current = PreviousTask;

                Current->Stack->Push(Result);

                break;

            }

            case op_arraylength: {

                Array* ArrayReference = (Array*)Current->Stack->TopAndPop();

                Current->Stack->Push(Pointer->Integer(ArrayReference->Length));

                break;

            }

            case op_astore: case op_dstore: case op_fstore: case op_istore: case op_lstore: {

                ManagedByte NumericalRegisterIndex = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Object* ObjectReference = Current->Stack->TopAndPop();

                Current->Registers->Set(NumericalRegisterIndex,ObjectReference);

                break;
            }

            case op_astore_0: case op_dstore_0: case op_fstore_0: case op_istore_0: case op_lstore_0: {

                Object* ObjectReference = Current->Stack->TopAndPop();

                Current->Registers->Set(0,ObjectReference);

                break;
            }

            case op_astore_1: case op_dstore_1: case op_fstore_1: case op_istore_1: case op_lstore_1: {

                Object* ObjectReference = Current->Stack->TopAndPop();

                Current->Registers->Set(1,ObjectReference);

                break;
            }

            case op_astore_2: case op_dstore_2: case op_fstore_2: case op_istore_2: case op_lstore_2: {

                Object* ObjectReference = Current->Stack->TopAndPop();

                Current->Registers->Set(2,ObjectReference);

                break;
            }

            case op_astore_3: case op_dstore_3: case op_fstore_3: case op_istore_3: case op_lstore_3: {

                Object* ObjectReference = Current->Stack->TopAndPop();

                Current->Registers->Set(3,ObjectReference);

                break;
            }

            // FIXME
            case op_athrow: {

                kassert(true,"[Executive] Exceptions is not implemented yet!");

                break;

            }

            case op_baload: {

                Integer* ArrayElementIndexReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                // FIXME
                printf("Loading index ");
                printInteger(ArrayElementIndexReference->Value);
                printf(" from ");
                printInteger((uintptr_t)(ArrayReference));
                printf(" array\n");

                Current->Stack->Push(Pointer->Integer(ArrayReference->GetByte(ArrayElementIndexReference->Value)));

                break;
            }

            case op_caload: case op_saload: {

                Integer* ArrayElementIndexReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                // FIXME
                printf("Loading index ");
                printInteger(ArrayElementIndexReference->Value);
                printf(" from ");
                printInteger((uintptr_t)(ArrayReference));
                printf(" array\n");

                Current->Stack->Push(Pointer->Integer(ArrayReference->GetCharacter(ArrayElementIndexReference->Value)));

                break;
            }

            case op_daload: {

                Integer* ArrayElementIndexReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                // FIXME
                printf("Loading index ");
                printInteger(ArrayElementIndexReference->Value);
                printf(" from ");
                printInteger((uintptr_t)(ArrayReference));
                printf(" array\n");

                Current->Stack->Push(Pointer->Double(ArrayReference->GetDouble(ArrayElementIndexReference->Value)));

                break;
            }

            case op_faload: {

                Integer* ArrayElementIndexReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                // FIXME
                printf("Loading index ");
                printInteger(ArrayElementIndexReference->Value);
                printf(" from ");
                printInteger((uintptr_t)(ArrayReference));
                printf(" array\n");

                Current->Stack->Push(Pointer->Float(ArrayReference->GetFloat(ArrayElementIndexReference->Value)));

                break;
            }

            case op_iaload: {

                Integer* ArrayElementIndexReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                // FIXME
                printf("Loading index ");
                printInteger(ArrayElementIndexReference->Value);
                printf(" from ");
                printInteger((uintptr_t)(ArrayReference));
                printf(" array\n");

                Current->Stack->Push(Pointer->Integer(ArrayReference->GetInteger(ArrayElementIndexReference->Value)));

                break;
            }

            case op_laload: {

                Integer* ArrayElementIndexReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                // FIXME
                printf("Loading index ");
                printInteger(ArrayElementIndexReference->Value);
                printf(" from ");
                printInteger((uintptr_t)(ArrayReference));
                printf(" array\n");

                Current->Stack->Push(Pointer->Long(ArrayReference->GetLong(ArrayElementIndexReference->Value)));

                break;
            }

            case op_sastore: case op_castore: {

                Integer* ArrayElementValueReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Integer* ArrayElementIndexReference = (Integer*)Current->Stack->TopAndPop();
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                ArrayReference->Set(ArrayElementIndexReference->Value,(short)ArrayElementValueReference->Value);

                break;
            }

            case op_bastore: {

                Integer* ArrayElementValueReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Integer* ArrayElementIndexReference = (Integer*)Current->Stack->TopAndPop();
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                ArrayReference->Set(ArrayElementIndexReference->Value,(ManagedByte)ArrayElementValueReference->Value);

                break;
            }

            case op_dastore: {

                Double* ArrayElementValueReference = static_cast<Double *>(Current->Stack->TopAndPop());
                Integer* ArrayElementIndexReference = (Integer*)Current->Stack->TopAndPop();
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                ArrayReference->Set(ArrayElementIndexReference->Value,(ManagedDouble)ArrayElementValueReference->Value);

                break;
            }

            case op_fastore: {

                Float* ArrayElementValueReference = static_cast<Float *>(Current->Stack->TopAndPop());
                Integer* ArrayElementIndexReference = (Integer*)Current->Stack->TopAndPop();
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                ArrayReference->Set(ArrayElementIndexReference->Value,(ManagedFloat)ArrayElementValueReference->Value);

                break;
            }

            case op_iastore: {

                Integer* ArrayElementValueReference = static_cast<Integer *>(Current->Stack->TopAndPop());
                Integer* ArrayElementIndexReference = (Integer*)Current->Stack->TopAndPop();
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                ArrayReference->Set(ArrayElementIndexReference->Value,(ManagedInteger)ArrayElementValueReference->Value);

                break;
            }

            case op_lastore: {

                Long* ArrayElementValueReference = static_cast<Long *>(Current->Stack->TopAndPop());
                Integer* ArrayElementIndexReference = (Integer*)Current->Stack->TopAndPop();
                Array* ArrayReference = reinterpret_cast<Array *>(Current->Stack->TopAndPop());

                ArrayReference->Set(ArrayElementIndexReference->Value,(ManagedLong)ArrayElementValueReference->Value);

                break;
            }



            case op_checkcast: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
/*
                // FIXME IMPLEMENT!
                kassert(true,"[Executive] Cast check is not implemented yet!");
*/
                break;
            }

            case op_d2f: {

                Double* Instance = (Double*)Current->Stack->TopAndPop();

                ManagedFloat FloatValue = (ManagedFloat)Instance->Value;

                Instance->Value = FloatValue;

                Current->Stack->Push(Instance);

                break;
            }

            case op_d2i: {

                Double* Instance = (Double*)Current->Stack->TopAndPop();

                 ManagedInteger  IntegerValue = ( ManagedInteger )Instance->Value;

                Instance->Value = IntegerValue;

                Current->Stack->Push(Instance);

                break;

            }

            case op_d2l: {

                Double* Instance = (Double*)Current->Stack->TopAndPop();

                ManagedLong LongValue = (ManagedLong)Instance->Value;

                Instance->Value = LongValue;

                Current->Stack->Push(Instance);

                break;
            }

            case op_dadd: {

                Double* First = (Double*)Current->Stack->TopAndPop();
                Double* Second = (Double*)Current->Stack->TopAndPop();

                ManagedDouble FinalValue = First->Value + Second->Value;

                Second->Value = FinalValue;

                Current->Stack->Push(Second);

                break;
            }

            // TODO IEEE 754 NAN???
            case op_dcmpg: case op_dcmpl: {

                Double* SecondDoubleReference = (Double*)Current->Stack->TopAndPop();
                Double* FirstDoubleReference = (Double*)Current->Stack->TopAndPop();

                 ManagedInteger  Result;

                if (SecondDoubleReference->Value > FirstDoubleReference->Value) {
                    Result = 1;
                }
                else if (SecondDoubleReference->Value == FirstDoubleReference->Value) {
                    Result = 0;
                }
                else {
                    Result = -1;
                }

                Current->Stack->Push(Pointer->Integer(Result));

                break;
            }

            case op_dconst_0: {

                double Constant = 0.0;

                Current->Stack->Push(Pointer->Double(Constant));

                break;
            }

            case op_dconst_1: {

                double Constant = 1.0;

                Current->Stack->Push(Pointer->Double(Constant));

                break;
            }

            case op_ddiv: {

                Double* SecondDoubleReference = (Double*)Current->Stack->TopAndPop();
                Double* FirstDoubleReference = (Double*)Current->Stack->TopAndPop();

                ManagedDouble FinalValue = FirstDoubleReference->Value/SecondDoubleReference->Value;

                SecondDoubleReference->Value = FinalValue;

                Current->Stack->Push(SecondDoubleReference);

                break;

            }

            case op_dmul: {

                Double* SecondDoubleReference = (Double*)Current->Stack->TopAndPop();
                Double* FirstDoubleReference = (Double*)Current->Stack->TopAndPop();

                double FinalValue = FirstDoubleReference->Value*SecondDoubleReference->Value;

                SecondDoubleReference->Value = FinalValue;

                Current->Stack->Push(SecondDoubleReference);

                break;
            }

            case op_dneg: {

                Double* DoubleReference = (Double*)Current->Stack->TopAndPop();

                DoubleReference->Value = -DoubleReference->Value;

                Current->Stack->Push(DoubleReference);

                break;

            }

            case op_drem: {

                Double* SecondDoubleReference = (Double*)Current->Stack->TopAndPop();
                Double* FirstDoubleReference = (Double*)Current->Stack->TopAndPop();

                double FinalValue = fmod(FirstDoubleReference->Value,SecondDoubleReference->Value);

                Current->Stack->Push(SecondDoubleReference);;

                break;
            }

            case op_dsub: {

                Double* SecondDoubleReference = (Double*)Current->Stack->TopAndPop();
                Double* FirstDoubleReference = (Double*)Current->Stack->TopAndPop();

                double FinalValue = FirstDoubleReference->Value-SecondDoubleReference->Value;

                Current->Stack->Push(SecondDoubleReference);

                break;
            }

            case op_dup: {

                Current->Stack->Push(Current->Stack->Top());

                break;
            }

            case op_dup_x1: {

                Object* FirstReference = Current->Stack->TopAndPop();
                Object* SecondReference = Current->Stack->TopAndPop();

                Current->Stack->Push(FirstReference);
                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);

                break;
            }

            case op_dup_x2: {

                Object* FirstReference = Current->Stack->TopAndPop();
                Object* SecondReference = Current->Stack->TopAndPop();
                Object* ThirdReference = Current->Stack->TopAndPop();

                Current->Stack->Push(FirstReference);
                Current->Stack->Push(ThirdReference);
                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);

                break;
            }

            case op_dup2: {

                Object* FirstReference = Current->Stack->TopAndPop();
                Object* SecondReference = Current->Stack->TopAndPop();

                Current->Stack->Push(FirstReference);
                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);
                Current->Stack->Push(SecondReference);

                break;
            }

            case op_dup2_x1: {

                Object* FirstReference = Current->Stack->TopAndPop();
                Object* SecondReference = Current->Stack->TopAndPop();
                Object* ThirdReference = Current->Stack->TopAndPop();

                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);
                Current->Stack->Push(ThirdReference);
                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);

                break;
            }

            case op_dup2_x2: {

                Object* FirstReference = Current->Stack->TopAndPop();
                Object* SecondReference = Current->Stack->TopAndPop();
                Object* ThirdReference = Current->Stack->TopAndPop();
                Object* FourthReference = Current->Stack->TopAndPop();

                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);
                Current->Stack->Push(FourthReference);
                Current->Stack->Push(ThirdReference);
                Current->Stack->Push(SecondReference);
                Current->Stack->Push(FirstReference);

                break;
            }

            case op_f2d: {

                Float* Value = static_cast<struct Float *>(Current->Stack->TopAndPop());

                double DoubleValue = Value->Value;

                Current->Stack->Push(Value);

                break;
            }

            case op_f2i: {

                Float* Value = static_cast<Float *>(Current->Stack->TopAndPop());

                ManagedInteger  IntegerValue = (int)Value->Value;

                Value->Value = IntegerValue;

                Current->Stack->Push(Value);

                break;
            }

            case op_f2l: {

                Float* Value = static_cast<Float *>(Current->Stack->TopAndPop());

                ManagedLong LongValue = (long)Value->Value;

                Value->Value = LongValue;

                Current->Stack->Push(Value);

                break;
            }

            case op_fadd: {

                Float* SecondFloatReference = (Float*)Current->Stack->TopAndPop();
                Float* FirstFloatReference = static_cast<Float *>(Current->Stack->TopAndPop());

                ManagedFloat FinalValue = FirstFloatReference->Value+SecondFloatReference->Value;

                SecondFloatReference->Value = FinalValue;

                Current->Stack->Push(SecondFloatReference);

                break;

            }

            case op_lcmp: {

                Long* SecondLongReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstLongReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondLongReference->Value;
                ManagedLong FirstValue = FirstLongReference->Value;

                ManagedInteger Result;

                if (FirstValue > SecondValue) {
                    Result = 1;
                }
                else if (FirstValue == SecondValue) {
                    Result = 0;
                }
                else {
                    Result = -1;
                }

                Current->Stack->Push(Pointer->Integer(Result));

                break;

            }

            case op_fcmpg: case op_fcmpl: {

                Float* SecondFloatReference = (Float*)Current->Stack->TopAndPop();
                Float* FirstDoubleReference = (Float*)Current->Stack->TopAndPop();

                ManagedFloat SecondValue = SecondFloatReference->Value;
                ManagedFloat FirstValue = FirstDoubleReference->Value;

                ManagedInteger Result;

                if (FirstValue > SecondValue) {
                    Result = 1;
                }
                else if (FirstValue == SecondValue) {
                    Result = 0;
                }
                else {
                    Result = -1;
                }

                Current->Stack->Push(Pointer->Integer(Result));

                break;

            }

            case op_fconst_0: {

                ManagedFloat Constant = 0.0;

                Current->Stack->Push(Pointer->Float(Constant));

                break;
            }

            case op_fconst_1: {

                ManagedFloat Constant = 1.0;

                Current->Stack->Push(Pointer->Float(Constant));

                break;

            }

            case op_fconst_2: {

                ManagedFloat Constant = 2.0;

                Current->Stack->Push(Pointer->Float(Constant));

                break;

            }

            case op_fdiv: {

                Float* SecondFloatReference = static_cast<Float *>(Current->Stack->TopAndPop());
                Float* FirstFloatReference = (Float*)Current->Stack->TopAndPop();

                ManagedFloat SecondValue = SecondFloatReference->Value;
                ManagedFloat FirstValue = FirstFloatReference->Value;

                ManagedFloat FinalValue = FirstValue/SecondValue;

                SecondFloatReference->Value = FinalValue;

                Current->Stack->Push(SecondFloatReference);

                break;

            }

            case op_fmul: {

                Float* SecondFloatReference = (Float*)Current->Stack->TopAndPop();
                Float* FirstFloatReference = (Float*)Current->Stack->TopAndPop();

                ManagedFloat SecondValue = SecondFloatReference->Value;
                ManagedFloat FirstValue = FirstFloatReference->Value;

                ManagedFloat FinalValue = FirstValue*SecondValue;

                SecondFloatReference->Value = FinalValue;

                Current->Stack->Push(SecondFloatReference);

                break;

            }

            case op_lookupswitch: {
                // FIXME
                // TODO IMPLEMENT ME
                //Object OffsetTemplate =  (4 - ((IP - CodeBytecode->Length) % 4));

                //Object Offset = IP+OffsetTemplate;

                kassert(true, "[Executive] Switch not implemented yet!");

                break;
            }

            case op_lneg: {

                Long* LongReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong ManagedLong = LongReference->Value;

                ManagedLong = -ManagedLong;

                LongReference->Value = ManagedLong;

                Current->Stack->Push(LongReference);

                break;

            }

            case op_fneg: {

                Float* FloatReference = (Float*)Current->Stack->TopAndPop();

                ManagedFloat ManagedFloat = FloatReference->Value;

                ManagedFloat = -ManagedFloat;

                FloatReference->Value = ManagedFloat;

                Current->Stack->Push(FloatReference);

                break;

            }
                // TODO REMOVE ALL LIBC FUNCTION INTO ANOTHER LIB
            case op_frem: {

                Float* SecondFloatReference = (Float*)Current->Stack->TopAndPop();
                Float* FirstFloatReference = (Float*)Current->Stack->TopAndPop();

                ManagedFloat SecondValue = SecondFloatReference->Value;
                ManagedFloat FirstValue = FirstFloatReference->Value;

                ManagedFloat FinalValue = fmod(FirstValue,SecondValue);

                // FIXME
                // TODO MAKE STACK VARIABLES!!!
                SecondFloatReference->Value = FinalValue;

                Current->Stack->Push(SecondFloatReference);

                break;

            }

            case op_fsub: {

                Float* SecondFloatReference = (Float*)Current->Stack->TopAndPop();
                Float* FirstFloatReference = (Float*)Current->Stack->TopAndPop();

                ManagedFloat SecondValue = SecondFloatReference->Value;
                ManagedFloat FirstValue = FirstFloatReference->Value;

                ManagedFloat FinalValue = FirstValue-SecondValue;

                // FIXME
                // TODO MAKE STACK VARIABLES!!!
                SecondFloatReference->Value = FinalValue;

                Current->Stack->Push(SecondFloatReference);

                break;

            }

            case op_putfield: {

                Object* Value = Current->Stack->TopAndPop();

                Object* ObjectReference = Current->Stack->TopAndPop();

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = FirstIndexByte << 8 | SecondIndexByte;

                Field* TargetField = static_cast<Field *>(Current->Link->Pool->GetObject(IndexByte));

                Class* TargetFieldClass = TargetField->Owner;

                long Offset = 0;

                int InitialIndex = 0;

                for (int i = 0; i < TargetFieldClass->Fields->Length; ++i) {
                    if (TargetFieldClass->Fields->GetObject(i) == TargetField) {
                        break;
                    }
                    else {
                        Offset += ((Field*)(TargetFieldClass->Fields->GetObject(i)))->Length;
                    }
                }

                Class* Super = TargetFieldClass->Super;

                while (Super) {

                    for (int i = 0; i < Super->Fields->Length; ++i) {
                        Offset += ((Field*)(Super->Fields->GetObject(i)))->Length;
                    }

                    Super = Super->Super;

                }

                char* Target = reinterpret_cast<char *>(ObjectReference);

                Target += Offset;

                // IMPLEMENT UTS STRUCT AND DELETE THIS HELL!!!
                // FIXME BAD MEMCPY long not double!!!

                switch (TargetField->Signature->Data->GetCharacter(0)) {
                    case 'B': case 'Z': {
                        printf("Putting value ");
                        printInteger(((Integer*)Value)->Value);
                        printf(" in field ");
                        TargetField->Name->Log();
                        println("");

                        memcpy(Target,&((Integer*)Value)->Value,sizeof (ManagedBoolean));
                        break;
                    }
                    case 'S': case 'C': {
                        printf("Putting value ");
                        printInteger(((Integer*)Value)->Value);
                        printf(" in field ");
                        TargetField->Name->Log();
                        println("");

                        memcpy(Target,&((Integer*)Value)->Value,sizeof (ManagedChar));
                        break;
                    }
                    case 'I': case 'F': {
                        printf("Putting value ");
                        printInteger(((Integer*)Value)->Value);
                        printf(" in field ");
                        TargetField->Name->Log();
                        println("");

                        memcpy(Target,&((Integer*)Value)->Value,sizeof (ManagedInteger));
                        break;
                    }
                    case 'J': case 'D': {
                        printf("Putting value ");
                        printInteger(((Long*)Value)->Value);
                        printf(" in field ");
                        TargetField->Name->Log();
                        println("");

                        memcpy(Target,&((Long*)Value)->Value,sizeof (ManagedLong));
                        break;
                    }
                    case 'L': case '[': {
                        printf("Putting address ");
                        printInteger((uintptr_t)Value);
                        printf(" in field ");
                        TargetField->Name->Log();
                        println("");

                        memcpy(Target,&Value,sizeof(uintptr_t));
                        break;
                    }
                }

                break;

            }

            case op_getfield: {

                Object* ObjectReference = Current->Stack->TopAndPop();

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = FirstIndexByte << 8 | SecondIndexByte;

                Field* TargetField = static_cast<Field *>(Current->Link->Pool->GetObject(IndexByte));

                Class* TargetFieldClass = TargetField->Owner;

                long Offset = 0;

                int InitialIndex = 0;

                for (int i = 0; i < TargetFieldClass->Fields->Length; ++i) {
                    if (TargetFieldClass->Fields->GetObject(i) == TargetField) {
                        break;
                    }
                    else {
                        Offset += ((Field*)(TargetFieldClass->Fields->GetObject(i)))->Length;
                    }
                }

                Class* Super = TargetFieldClass->Super;

                while (Super) {

                    for (int i = 0; i < Super->Fields->Length; ++i) {
                        Offset += ((Field*)(Super->Fields->GetObject(i)))->Length;
                    }

                    Super = Super->Super;

                }

                char* Target = reinterpret_cast<char *>(ObjectReference);

                Target += Offset;

                switch (TargetField->Signature->Data->GetCharacter(0)) {

                    case 'L': case '[': {
                        auto** Value = reinterpret_cast<Object **>(Target);

                        Current->Stack->Push(*(Value));
                        break;
                    }
                    case 'J': {
                        ManagedLong Value = *(ManagedLong*)Target;

                        Current->Stack->Push(Pointer->Long(Value));

                        printf("Getting value ");
                        printInteger(Value);
                        printf(" from field ");
                        TargetField->Name->Log();
                        println("");
                        break;
                    }
                    case 'D': {
                        ManagedDouble Value = *(ManagedDouble*)Target;

                        Current->Stack->Push(Pointer->Double(Value));

                        printf("Getting value ");
                        printInteger(Value);
                        printf(" from field ");
                        TargetField->Name->Log();
                        println("");
                        break;
                    }
                    case 'F': {
                        ManagedFloat Value = *(ManagedFloat*)Target;

                        Current->Stack->Push(Pointer->Float(Value));

                        printf("Getting value ");
                        printInteger(Value);
                        printf(" from field ");
                        TargetField->Name->Log();
                        println("");
                        break;
                    }
                    case 'I': {
                        ManagedInteger Value = *(ManagedInteger*)Target;

                        Current->Stack->Push(Pointer->Integer(Value));

                        printf("Getting value ");
                        printInteger(Value);
                        printf(" from field ");
                        TargetField->Name->Log();
                        println("");
                        break;
                    }
                    case 'Z': case 'B': {
                        u1 Value = *Target;

                        Current->Stack->Push(Pointer->Integer(Value));

                        printf("Getting value ");
                        printInteger(Value);
                        printf(" from field ");
                        TargetField->Name->Log();
                        println("");
                        break;
                    }
                    case 'C': case 'S': {
                        u2 Value = *(ManagedChar*)Target;

                        Current->Stack->Push(Pointer->Integer(Value));

                        printf("Getting value ");
                        printInteger(Value);
                        printf(" from field ");
                        TargetField->Name->Log();
                        println("");
                        break;
                    }
                };
                break;
            }

            case op_putstatic: {

                Object* Value = Current->Stack->TopAndPop();

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = FirstIndexByte | SecondIndexByte;

                Field* Field = static_cast<struct Field *>(Current->Link->Pool->GetObject(IndexByte));

                Field->Value = Value;

                break;

            }

            case op_getstatic: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = FirstIndexByte | SecondIndexByte;

                Field* Field = static_cast<struct Field *>(Current->Link->Pool->GetObject(IndexByte));

                Current->Stack->Push(Field->Value);

                break;

            }

            case op_goto: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 FinalPointer = FirstIndexByte << 8 | SecondIndexByte;

                printf("Jumping to ");
                printInteger(Current->Counter+FinalPointer-1-sizeof(s2));
                printf(" address\n");

                Current->Counter = Current->Counter+FinalPointer-1-sizeof(s2);

                break;
            }

            case op_jsr: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 FinalPointer = FirstIndexByte << 8 | SecondIndexByte;

                Current->Stack->Push(Pointer->Long(Current->Counter));

                Current->Counter += FinalPointer-1-sizeof(s2);

                break;
            }

            case op_goto_w: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 ThirdIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 FourthIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s4 FinalPointer = (FirstIndexByte << 24) | (SecondIndexByte << 16) | (ThirdIndexByte << 8) | FourthIndexByte;

                Current->Counter += FinalPointer-1-sizeof(s4);

                break;
            }

            case op_ret: {

                u1 RegisterIndex = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Long* ReturnAddress = (Long*)Current->Registers->GetObject(RegisterIndex);

                Current->Counter = ReturnAddress->Value-1;

                break;
            }

            case op_jsr_w: {


                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 ThirdIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 FourthIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 FinalPointer = (FirstIndexByte << 24) | (SecondIndexByte << 16) | (ThirdIndexByte << 8) | FourthIndexByte;

                Current->Stack->Push(Pointer->Long(Current->Counter));

                Current->Counter += FinalPointer-1-sizeof(s4);

                break;

            }

            case op_i2b: {

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger IntegerValue = Value->Value;

                ManagedByte ByteValue = (ManagedByte)IntegerValue;

                Value->Value = ByteValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_i2c: case op_i2s: {

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger IntegerValue = Value->Value;

                auto ByteValue = (ManagedShort)IntegerValue;

                Value->Value = ByteValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_i2d: {

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger IntegerValue = Value->Value;

                ManagedDouble ByteValue = (ManagedDouble)IntegerValue;

                Value->Value = ByteValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_i2f: {

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger IntegerValue = Value->Value;

                ManagedFloat ByteValue = (ManagedFloat)IntegerValue;

                Value->Value = ByteValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_l2f: {

                Long* Value = (Long*)Current->Stack->TopAndPop();

                ManagedLong LongValue = Value->Value;

                ManagedFloat FloatValue = (ManagedFloat)LongValue;

                Value->Value = FloatValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_l2i: {

                Long* Value = (Long*)Current->Stack->TopAndPop();

                ManagedLong LongValue = Value->Value;

                ManagedInteger IntegerValue = (int)LongValue;

                Value->Value = IntegerValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_l2d: {

                Long* Value = (Long*)Current->Stack->TopAndPop();

                ManagedLong LongValue = Value->Value;

                ManagedDouble DoubleValue = (ManagedDouble)LongValue;

                Value->Value = DoubleValue;

                Current->Stack->Push(Value);

                break;

            }

            case op_i2l: {

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger IntegerValue = Value->Value;

                ManagedLong LongValue = (long)IntegerValue;

                Value->Value = LongValue;

                Current->Stack->Push(Value);

                break;
            }

            case op_iadd: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue+SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_ladd: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue+SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;

            }

            case op_lsub: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue-SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;

            }

            case op_ldiv : {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                // FIXME divdi3
                long SecondValue = SecondValueReference->Value;
                long FirstValue = FirstValueReference->Value;

                long FinalValue = FirstValue/SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;

            }

            case op_lconst_0: {

                Current->Stack->Push(Pointer->Long(0));

                break;

            }

            case op_ldc_w: case op_ldc2_w: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = FirstIndexByte | SecondIndexByte;

                Array* Pool = Current->Link->Pool;

                Current->Stack->Push(Pool->GetObject(IndexByte));

                break;
            }

            case op_ldc: {

                u1 IndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Array* Pool = Current->Link->Pool;

                Current->Stack->Push(Pool->GetObject(IndexByte));

                break;
            }

            case op_lconst_1: {

                Current->Stack->Push(Pointer->Long(1));

                break;
            }

            case op_lrem: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                // FIXME divd3
                long SecondValue = SecondValueReference->Value;
                long FirstValue = FirstValueReference->Value;

                long FinalValue = FirstValue - (FirstValue/SecondValue) * SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_irem: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue - (FirstValue/SecondValue) * SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_ishl: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue << SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_lshl: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue << SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_monitorenter: {
                // TODO IMPLEMENT ME
                kassert(true, "[Executive] Monitor enter not implemented yet!");

                break;
            }

            case op_monitorexit: {
                // TODO IMPLEMENT ME
                kassert(true, "[Executive] Monitor exit not implemented yet!");

                break;
            }

            case op_lxor: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue ^ SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;

            }

            case op_ixor: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue ^ SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_ishr: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue >> SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_lshr: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue >> SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);
                break;
            }

            case op_iushr: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;

                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue >> SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_lushr: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;

                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue >> SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_isub: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue - SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_lor: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue | SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_ior: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue | SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_lmul: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue*SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_land: {

                Long* SecondValueReference = (Long*)Current->Stack->TopAndPop();
                Long* FirstValueReference = (Long*)Current->Stack->TopAndPop();

                ManagedLong SecondValue = SecondValueReference->Value;
                ManagedLong FirstValue = FirstValueReference->Value;

                ManagedLong FinalValue = FirstValue&SecondValue;

                Object* Final = Pointer->Long(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_iand: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue & SecondValue;

                Object* Final = Pointer->Integer(FinalValue);

                Current->Stack->Push(Final);

                break;
            }

            case op_iconst_m1: {

                Current->Stack->Push(Pointer->Integer(-1));

                break;
            }

            case op_iconst_0: {
                Current->Stack->Push(Pointer->Integer(0));

                break;
            }

            case op_iconst_1: {
                Current->Stack->Push(Pointer->Integer(1));

                break;
            }

            case op_iconst_2: {
                Current->Stack->Push(Pointer->Integer(2));

                break;
            }

            case op_iconst_3: {
                Current->Stack->Push(Pointer->Integer(3));

                break;
            }

            case op_iconst_4: {
                Current->Stack->Push(Pointer->Integer(4));

                break;
            }

            case op_iconst_5: {
                Current->Stack->Push(Pointer->Integer(5));

                break;
            }

            case op_idiv: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue/SecondValue;

                SecondValueReference->Value = FinalValue;

                Current->Stack->Push(SecondValueReference);

                break;

            }

            case op_if_acmpeq: case op_if_acmpne: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Object* SecondValueReference = Current->Stack->TopAndPop();
                Object* FirstValueReference = Current->Stack->TopAndPop();

                if  (SecondValueReference == FirstValueReference) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                kassert(true,"[Executive] equals for objects is not implemented yet!");
                break;

            }

            case op_if_icmpeq: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                if (FirstValue == SecondValue) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;
            }

            case op_multianewarray: {

                // TODO IMPLEMENT ME
                kassert(true, "[Executive] Multidimensional arrays not implemented yet!");

                break;

            }

            case op_if_icmpne: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                if (FirstValue != SecondValue) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;
            }


            case op_if_icmplt: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                if (FirstValue < SecondValue) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_if_icmple: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger  SecondValue = SecondValueReference->Value;
                ManagedInteger  FirstValue = FirstValueReference->Value;

                if (FirstValue <= SecondValue) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_if_icmpgt: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                if (FirstValue > SecondValue) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_if_icmpge: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger  SecondValue = SecondValueReference->Value;
                ManagedInteger  FirstValue = FirstValueReference->Value;

                if (FirstValue >= SecondValue) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_ifeq: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger FirstValue = Value->Value;

                if (FirstValue == 0) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_ifne: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger FirstValue = Value->Value;

                if (FirstValue != 0) {
                    // FIXME
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_iflt: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger FirstValue = Value->Value;

                if (FirstValue < 0) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_ifle: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger FirstValue = Value->Value;

                if (FirstValue <= 0) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;

            }

            case op_ifgt: {
                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger FirstValue = Value->Value;

                if (FirstValue > 0) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;
            }

            case op_ifge: {
                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Integer* Value = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger FirstValue = Value->Value;

                if (FirstValue >= 0) {
                    Current->Counter += IndexByte-1-sizeof(s2);
                }

                break;
            }

            case op_ifnonnull: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 FinalPointer = FirstIndexByte << 8 | SecondIndexByte;

                Object* Value = Current->Stack->TopAndPop();

                if (Value != nullptr) {
                    Current->Counter += FinalPointer-1;
                }

                break;

            }

            case op_ifnull: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 FinalPointer = FirstIndexByte << 8 | SecondIndexByte;

                Object* Value = Current->Stack->TopAndPop();

                if (Value == nullptr) {
                    Current->Counter += FinalPointer-1;
                }

                break;

            }

            case op_iinc: {

                u1 RegisterIndex = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s1 IncrementConstant = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Integer* Local = (Integer*)Current->Registers->GetObject(RegisterIndex);

                Local->Value += IncrementConstant;

                break;

            }

            case op_imul: {

                Integer* SecondValueReference = (Integer*)Current->Stack->TopAndPop();
                Integer* FirstValueReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger SecondValue = SecondValueReference->Value;
                ManagedInteger FirstValue = FirstValueReference->Value;

                ManagedInteger FinalValue = FirstValue*SecondValue;

                SecondValueReference->Value = FinalValue;

                Current->Stack->Push(SecondValueReference);

                break;
            }

            case op_ineg: {

                Integer* IntegerReference = (Integer*)Current->Stack->TopAndPop();

                ManagedInteger Value = IntegerReference->Value;

                Value = -Value;

                IntegerReference->Value = Value;

                Current->Stack->Push(IntegerReference);

                break;
            }

            case op_instanceof: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                // TODO IMPLEMENT!!!

                Class* targetClass = static_cast<Class *>(Current->Link->Pool->GetObject(IndexByte));
                Object* ObjectReference = Current->Stack->TopAndPop();

                //kassert(true,"[Executive] Type checking for objects is not implemented yet!");

                break;

            }

            case op_invokeinterface: {

                //
                // Resolving method
                //

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 Unused = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondUnused = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte | SecondIndexByte;

                Method* Executable = (Method*)Current->Link->Pool->GetObject(IndexByte);

                if (Executable == nullptr) {
                    printf("Failed to resolve method!\n");
                }

                //
                //  Signature parsing
                //

                u4 ArgumentCounter = 0;


                for (size_t i = 1; i < Executable->Signature->Length; ++i) {

                    switch (Executable->Signature->Data->GetCharacter(i)) {
                        case ')': {
                            goto InterfacePushArgs;;
                            break;
                        }
                        case 'B': case 'C': case 'D': case 'F': case 'I': case 'J': case 'S': case 'Z': {
                            ArgumentCounter++;
                            break;
                        }
                        case '[': {
                            break;
                        }
                        case 'L': {
                            ArgumentCounter++;

                            while (Executable->Signature->Data->GetCharacter(i) != ';') {
                                i++;
                            }

                            break;
                        }
                    }
                }

                InterfacePushArgs:

                //
                // Pushing arguments
                //

                Object* Arguments[ArgumentCounter];

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Arguments[ArgumentCounter-i-1] = Current->Stack->TopAndPop();
                }

                Object* ObjectReference = Current->Stack->TopAndPop();

                //
                // ABI PART
                //

                Class* TargetClass = ObjectReference->Instance;

                Method* TargetMethod = nullptr;

                ManagedBoolean Linked = false;

                while (TargetMethod == nullptr) {
                    for (int i = 0; i < TargetClass->Methods->Length; ++i) {
                        Method* Find = static_cast<Method *>(TargetClass->Methods->GetObject(i));

                        if (Executable->Signature->Equals(Find->Signature) && Executable->Name->Equals(Find->Name)) {
                            TargetMethod = Find;
                            if (TargetMethod->Instructions) {
                                Linked = true;
                                Executable = TargetMethod;
                                break;
                            }
                        }
                        if (Linked) {
                            break;
                        }
                    }
                    TargetClass = TargetClass->Super;
                    if (Linked) {
                        break;
                    }
                }

                if (Executable->Instructions == nullptr) {
                    if (!Executive::HALCall(Executable,Arguments,Current)) {
                        printf("[Executive] Could not find implementation for ");
                        Executable->Owner->Name->Log();
                        printf(":");
                        Executable->Name->Log();
                        printf(".");
                        Executable->Signature->Log();
                        println("");
                        kassert(true, "[Executive] Native!!!");
                    }

                    continue;
                }

                // bad? FIXME
                printf("Calling interface method: ");
                Executable->Owner->Name->Log();
                printf(".");
                Executable->Name->Log();
                printf("::");
                Executable->Signature->Log();
                println("");

                Task* NewTask = Pointer->Task();

                NewTask->Stack = Pointer->Stack(Executable->Instructions->Stack + ABISpace);
                NewTask->Registers = Pointer->List(Executable->Instructions->Registers);

                NewTask->Registers->Set(0,ObjectReference);

                NewTask->Stack->Push(Current);

                NewTask->Instructions = Executable->Instructions;
                NewTask->Link = Executable->Owner;

                NewTask->Counter = -1;

                Current = NewTask;

                //
                // Pushing arguments to destination stack
                //

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Current->Registers->Set(i+1,Arguments[i]);
                }

                break;

            }


            case op_new: {

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                u2 IndexByte = FirstIndexByte | SecondIndexByte;

                Class* Instantiable = (Class*)Current->Link->Pool->GetObject(IndexByte);

                printf("Allocating new ");
                Instantiable->Name->Log();
                println(" instance");

                Current->Stack->Push(static_cast<Object *>(Pointer->Allocate(Instantiable)));

                break;

            }

            case op_newarray: {

                // FIXME
                volatile s1 Type = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                Integer* Length = (Integer*)Current->Stack->TopAndPop();

                Current->Stack->Push(reinterpret_cast<Object *>(Pointer->List(Length->Value)));

                break;
            }

            case op_nop: {

                break;

            }

            case op_pop: {

                Current->Stack->Pop();

                break;
            }

            case op_pop2: {

                Current->Stack->Pop();
                Current->Stack->Pop();

                break;
            }

            case op_invokespecial: {

                //
                // Resolving method
                //

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte << 8 | SecondIndexByte;

                Method* Executable = (Method*)Current->Link->Pool->GetObject(IndexByte);

                //
                //  Signature parsing
                //

                u4 ArgumentCounter = 0;

                for (size_t i = 1; i < Executable->Signature->Length; ++i) {

                    switch (Executable->Signature->Data->GetCharacter(i)) {
                        case ')': {
                            goto SpecialPushArgs;
                            break;
                        }
                        case 'B': case 'C': case 'D': case 'F': case 'I': case 'J': case 'S': case 'Z': {
                            ArgumentCounter++;
                            break;
                        }
                        case '[': {
                            break;
                        }
                        case 'L': {
                            ArgumentCounter++;

                            while (Executable->Signature->Data->GetCharacter(i) != ';') {
                                i++;
                            }

                            break;
                        }
                    }
                }

                SpecialPushArgs:

                //
                // Pushing arguments
                //

                Object* Arguments[ArgumentCounter];

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Arguments[ArgumentCounter-i-1] = Current->Stack->TopAndPop();
                }

                Object* ObjectReference = Current->Stack->TopAndPop();

                //
                //  Resolving superclass method
                //

                // FIXME

                Class* TargetClass = Executable->Owner->Super;
/*
                Method* TargetMethod = nullptr;

                while (!TargetMethod) {

                    for (int i = 0; i < TargetClass->Methods->Length; ++i) {

                        Method* Find = (Method*)TargetClass->Methods->GetObject(i);

                        if (Executable->Signature->Equals(Find->Signature) && Executable->Name->Equals(Find->Name)) {
                            TargetMethod = Find;
                        }

                    }

                }
*/
                //
                // ABI PART
                //

                if (Executable->Instructions == nullptr) {
                    if (!Executive::HALCall(Executable,Arguments,Current)) {
                        printf("[Executive] Could not find implementation for ");
                        Executable->Owner->Name->Log();
                        printf(":");
                        Executable->Name->Log();
                        printf(".");
                        Executable->Signature->Log();
                        println("");
                        kassert(true, "[Executive] Native!!!");
                    }

                    continue;
                }

                printf("Calling special method: ");
                Executable->Owner->Name->Log();
                printf(".");
                Executable->Name->Log();
                printf("::");
                Executable->Signature->Log();
                println("");

                Task* NewTask = Pointer->Task();

                NewTask->Stack = Pointer->Stack(Executable->Instructions->Stack + ABISpace);
                NewTask->Registers = Pointer->List(Executable->Instructions->Registers);

                NewTask->Registers->Set(0,ObjectReference);

                NewTask->Stack->Push(Current);

                NewTask->Instructions = Executable->Instructions;
                NewTask->Link = Executable->Owner;

                NewTask->Counter = -1;

                Current = NewTask;

                //
                // Pushing arguments to destination stack
                //

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Current->Registers->Set(ArgumentCounter-i,Arguments[i]);
                }

                break;

            }

            case op_invokestatic: {

                //
                // Resolving method
                //

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte << 8 | SecondIndexByte;

                Method* Executable = static_cast<Method *>(Current->Link->Pool->GetObject(IndexByte));

                //
                //  Signature parsing
                //

                u4 ArgumentCounter = 0;

                for (size_t i = 1; i < Executable->Signature->Length; ++i) {

                    switch (Executable->Signature->Data->GetCharacter(i)) {
                        case ')': {
                            goto StaticPushArgs;
                            break;
                        }
                        case 'B': case 'C': case 'D': case 'F': case 'I': case 'J': case 'S': case 'Z': {
                            ArgumentCounter++;
                            break;
                        }
                        case '[': {
                            break;
                        }
                        case 'L': {
                            ArgumentCounter++;

                            while (Executable->Signature->Data->GetCharacter(i) != ';') {
                                i++;
                            }

                            break;
                        }
                    }
                }

                StaticPushArgs:

                //
                // Pushing arguments
                //

                Object* Arguments[ArgumentCounter];

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Arguments[ArgumentCounter-i-1] = Current->Stack->TopAndPop();
                }

                //
                // ABI PART
                //

                printf("Calling static method: ");
                Executable->Owner->Name->Log();
                printf(".");
                Executable->Name->Log();
                printf("::");
                Executable->Signature->Log();
                println("");

                if (Executable->Instructions == nullptr) {

                    if (!Executive::HALCall(Executable,Arguments,Current)) {
                        printf("[Executive] Could not find implementation for ");
                        Executable->Owner->Name->Log();
                        printf(":");
                        Executable->Name->Log();
                        printf(".");
                        Executable->Signature->Log();
                        println("");
                        kassert(true, "[Executive] Native!!!");
                    }

                    continue;

                }

                Task* NewTask = Pointer->Task();

                NewTask->Stack = Pointer->Stack(Executable->Instructions->Stack + ABISpace);
                NewTask->Registers = Pointer->List(Executable->Instructions->Registers);

                NewTask->Counter = -1;

                NewTask->Stack->Push(Current);

                NewTask->Instructions = Executable->Instructions;
                NewTask->Link = Executable->Owner;

                Current = NewTask;

                //
                // Pushing arguments to destination stack
                //

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Current->Registers->Set(i,Arguments[i]);
                }

                break;

            }

            case op_invokevirtual: {

                //
                // Resolving method
                //

                u1 FirstIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);
                u1 SecondIndexByte = Current->Instructions->Bytecode->GetByte(++Current->Counter);

                s2 IndexByte = FirstIndexByte << 8 | SecondIndexByte;

                Method* Executable = (Method*)Current->Link->Pool->GetObject(IndexByte);

                //
                //  Signature parsing
                //

                u4 ArgumentCounter = 0;

                for (size_t i = 1; i < Executable->Signature->Length; ++i) {
                    switch (Executable->Signature->Data->GetCharacter(i)) {
                        case ')': {
                            goto VirtualPushArgs;
                        }
                        case 'B': case 'C': case 'D': case 'F': case 'I': case 'J': case 'S': case 'Z': {
                            ArgumentCounter++;
                            break;
                        }
                        case '[': {
                            break;
                        }
                        case 'L': {
                            ArgumentCounter++;

                            while (Executable->Signature->Data->GetCharacter(i) != ';') {
                                i++;
                            }

                            break;
                        }
                    }
                }

                VirtualPushArgs:

                //
                // Pushing arguments
                //

                Object* Arguments[ArgumentCounter];

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Arguments[ArgumentCounter-i-1] = Current->Stack->TopAndPop();
                }

                Object* ObjectReference = Current->Stack->TopAndPop();

                //
                //  Resolving superclass method
                //

                Class* TargetClass = ObjectReference->Instance;

                switch (ObjectReference->Native) {

                    case NClass:
                    case NMethod:
                    case NField:
                    case NTask:
                    case NString:
                    case NVector:
                        TargetClass = Executable->Owner;
                        break;
                }

                Method* TargetMethod = nullptr;

                while (TargetMethod == nullptr) {
                    for (int i = 0; i < TargetClass->Methods->Length; ++i) {
                        Method* Find = static_cast<Method *>(TargetClass->Methods->GetObject(i));

                        if (Executable->Signature->Equals(Find->Signature) && Executable->Name->Equals(Find->Name)) {
                            TargetMethod = Find;
                            if (TargetMethod->Instructions != nullptr) {
                                Executable = TargetMethod;
                                goto VirtualABIPart;
                            }
                        }
                    }
                    TargetClass = TargetClass->Super;
                }

                //
                // ABI PART
                //

                VirtualABIPart:

                if (Executable->Instructions == nullptr) {

                    if (!Executive::HALCall(Executable,Arguments,Current)) {
                        printf("[Executive] Could not find implementation for ");
                        Executable->Owner->Name->Log();
                        printf(":");
                        Executable->Name->Log();
                        printf(".");
                        Executable->Signature->Log();
                        println("");
                        kassert(true, "[Executive] Native!!!");
                    }

                    continue;

                }

                printf("Calling virtual method: ");
                Executable->Owner->Name->Log();
                printf(".");
                Executable->Name->Log();
                printf("::");
                Executable->Signature->Log();
                println("");

                Task* NewTask = Pointer->Task();

                NewTask->Stack = Pointer->Stack(Executable->Instructions->Stack + 1);
                NewTask->Registers = Pointer->List(Executable->Instructions->Registers);

                NewTask->Registers->Set(0,ObjectReference);

                NewTask->Stack->Push(Current);

                NewTask->Instructions = Executable->Instructions;
                NewTask->Link = Executable->Owner;

                NewTask->Counter = -1;

                Current = NewTask;

                //
                // Pushing arguments to destination stack
                //

                for (size_t i = 0; i < ArgumentCounter; ++i) {
                    Current->Registers->Set(ArgumentCounter-i,Arguments[i]);
                }

                break;

            }

            default: {

                printf("Emitting invalid opcode: ");

                kassert(true, "[Executive] Unknown opcode!");

                break;
            }
        }

        CriticalEnd();

    }
}

bool Executive::HALCall(Method *Executable, Object **Arguments, Task *currentTask) {
    String* functionName = Executable->Name;

    if (functionName->Equals("out")) {
        String* ArgumentString = static_cast<String *>(Arguments[0]);

        ArgumentString->Print();

        return true;
    }
    else if (functionName->Equals("SpaceWrite")) {
        Integer* value = static_cast<Integer *>(Arguments[0]);
        Integer* type = static_cast<Integer *>(Arguments[1]);
        Integer* index = static_cast<Integer *>(Arguments[2]);

        SpaceWrite(index->Value,type->Value,value->Value);

        return true;
    }
    else if (functionName->Equals("SpaceRead")) {
        Integer* index = static_cast<Integer *>(Arguments[0]);
        Integer* type = static_cast<Integer *>(Arguments[1]);

        SpaceRead(index->Value,type->Value);

        return true;
    }

    return false;
}

void Executive::Interrupt(const s4 Index) {
    Interrupted = true;
    Task* InterruptEntry = Pointer->Task();

    InterruptEntry->Stack = Pointer->Stack(15);
    InterruptEntry->Registers = Pointer->List(15);

    InterruptEntry->Link = BRVR;
    InterruptEntry->Instructions = Route->Instructions;

    InterruptEntry->Counter = 0;
    InterruptEntry->Registers->Set(0,Pointer->Integer(Index));

    Executive::Execute(InterruptEntry);
    Interrupted = false;
}
