#define KiB     1024u       /*! Kibi 0x0000000000000400 */
#define MiB     1048576u    /*! Mebi 0x0000000000100000 */
#define GiB     1073741824u /*! Gibi 000000000040000000 */

/*
 * Sizes
 */
#define	BI2BY		8			/* bits per byte */
#define	BI2WD		32			/* bits per word */
#define	BY2WD		4			/* bytes per word */
#define	BY2V		8			/* bytes per double word */
#define	BY2PG		4096			/* bytes per page */
#define	WD2PG		(BY2PG/BY2WD)		/* words per page */
#define	PGSHIFT		12			/* log(BY2PG) */
#define	ROUND(s, sz)	(((s)+((sz)-1))&~((sz)-1))
#define	PGROUND(s)	ROUND(s, BY2PG)

#define KSTKSIZE    (8*KiB)
#define KSTACK      KSTKSIZE

/*
 * Fundamental addresses
 */
#define	MACHADDR	0x8002d000		/* as seen by current processor */
#define	MACHSIZE	BY2PG
#define TRAPSTACK	0x8003fff0

/*
 *  Address spaces
 */
#define RAMZERO		0x80000000			/* Start of usable RAM */
#define	UZERO		0x80040000			/* base of user address space */
#define	UTZERO		(UZERO+BY2PG)		/* first address in user text */
#define	KZERO		0x80300000		/* base of kernel address space */
#define	KTZERO		0x80400000		/* first address in kernel text */
#define	USTKTOP		(KZERO-BY2PG)		/* byte just beyond user stack */
#define	USTKSIZE	(1*MiB)		/* size of user stack */
#define	TSTKTOP		(USTKTOP-USTKSIZE)	/* end of new stack in sysexec */
#define	TSTKSIZ 	100
