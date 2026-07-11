if (RAM_GB <= 4) 
{
    // Eliminate high-quality animation tick rates for distant AI
    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("a.URO.Enable 1"));
    // Reduce the number of sound channels to free up Audio RAM
    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("au.MaxChannels 16"));
}
