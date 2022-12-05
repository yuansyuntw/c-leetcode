bool isInterleave(char *s1, char *s2, char *s3)
{
	int s1Length = strlen(s1);
	int s2Length = strlen(s2);
	int s3Length = strlen(s3);
	if (s1Length + s2Length != s3Length)
		return false;

	int **dp = (int **)calloc(s1Length + 1, sizeof(int *));
	for (int i = 0; i < s1Length + 1; i++)
	{
		dp[i] = (int *)calloc(s2Length + 1, sizeof(int));
	}

	dp[s1Length][s2Length] = 1;

	for (int index1 = s1Length; index1 >= 0; index1--)
	{
		for (int index2 = s2Length; index2 >= 0; index2--)
		{
			// Index 1 and index 2 can present the current s3 string.

			// Two paths

			// 1. right
			if ((index1 < s1Length) && (s1[index1] == s3[index1 + index2]) && dp[index1 + 1][index2])
			{
				dp[index1][index2] = 1;
			}

			// 2. down
			if ((index2 < s2Length) && (s2[index2] == s3[index1 + index2]) && dp[index1][index2 + 1])
			{
				dp[index1][index2] = 1;
			}
		}
	}

	int result = dp[0][0];

	for (int i = 0; i < s1Length - 1; i++)
	{
		free(dp[i]);
	}
	free(dp);

	return result;
}