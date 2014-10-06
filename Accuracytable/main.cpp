#include "global.h"
#include "memorypool.h"


// Multiround Trustgame estimation by A.Hula, with eternal gratefulness to A.Morhammer 
// Current Version, 9.September.2014

/*

GNU GENERAL PUBLIC LICENSE
Version 3, 29 June 2007
Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.
Preamble
The GNU General Public License is a free, copyleft license for
software and other kinds of works.
The licenses for most software and other practical works are designed
to take away your freedom to share and change the works. By contrast,
the GNU General Public License is intended to guarantee your freedom to
share and change all versions of a program--to make sure it remains free
software for all its users. We, the Free Software Foundation, use the
GNU General Public License for most of our software; it applies also to
any other work released this way by its authors. You can apply it to
your programs, too.
When we speak of free software, we are referring to freedom, not
price. Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
them if you wish), that you receive source code or can get it if you
want it, that you can change the software or use pieces of it in new
free programs, and that you know you can do these things.
To protect your rights, we need to prevent others from denying you
these rights or asking you to surrender the rights. Therefore, you have
certain responsibilities if you distribute copies of the software, or if
you modify it: responsibilities to respect the freedom of others.
For example, if you distribute copies of such a program, whether
gratis or for a fee, you must pass on to the recipients the same
freedoms that you received. You must make sure that they, too, receive
or can get the source code. And you must show them these terms so they
know their rights.
Developers that use the GNU GPL protect your rights with two steps:
(1) assert copyright on the software, and (2) offer you this License
giving you legal permission to copy, distribute and/or modify it.
For the developers' and authors' protection, the GPL clearly explains
that there is no warranty for this free software. For both users' and
authors' sake, the GPL requires that modified versions be marked as
changed, so that their problems will not be attributed erroneously to
authors of previous versions.
Some devices are designed to deny users access to install or run
modified versions of the software inside them, although the manufacturer
can do so. This is fundamentally incompatible with the aim of
protecting users' freedom to change the software. The systematic
pattern of such abuse occurs in the area of products for individuals to
use, which is precisely where it is most unacceptable. Therefore, we
have designed this version of the GPL to prohibit the practice for those
products. If such problems arise substantially in other domains, we
stand ready to extend this provision to those domains in future versions
of the GPL, as needed to protect the freedom of users.
Finally, every program is threatened constantly by software patents.
States should not allow patents to restrict development and use of
software on general-purpose computers, but in those that do, we wish to
avoid the special danger that patents applied to a free program could
make it effectively proprietary. To prevent this, the GPL assures that
patents cannot be used to render the program non-free.
The precise terms and conditions for copying, distribution and
modification follow.
TERMS AND CONDITIONS
0. Definitions.
"This License" refers to version 3 of the GNU General Public License.
"Copyright" also means copyright-like laws that apply to other kinds of
works, such as semiconductor masks.
"The Program" refers to any copyrightable work licensed under this
License. Each licensee is addressed as "you". "Licensees" and
"recipients" may be individuals or organizations.
To "modify" a work means to copy from or adapt all or part of the work
in a fashion requiring copyright permission, other than the making of an
exact copy. The resulting work is called a "modified version" of the
earlier work or a work "based on" the earlier work.
A "covered work" means either the unmodified Program or a work based
on the Program.
To "propagate" a work means to do anything with it that, without
permission, would make you directly or secondarily liable for
infringement under applicable copyright law, except executing it on a
computer or modifying a private copy. Propagation includes copying,
distribution (with or without modification), making available to the
public, and in some countries other activities as well.
To "convey" a work means any kind of propagation that enables other
parties to make or receive copies. Mere interaction with a user through
a computer network, with no transfer of a copy, is not conveying.
An interactive user interface displays "Appropriate Legal Notices"
to the extent that it includes a convenient and prominently visible
feature that (1) displays an appropriate copyright notice, and (2)
tells the user that there is no warranty for the work (except to the
extent that warranties are provided), that licensees may convey the
work under this License, and how to view a copy of this License. If
the interface presents a list of user commands or options, such as a
menu, a prominent item in the list meets this criterion.
1. Source Code.
The "source code" for a work means the preferred form of the work
for making modifications to it. "Object code" means any non-source
form of a work.
A "Standard Interface" means an interface that either is an official
standard defined by a recognized standards body, or, in the case of
interfaces specified for a particular programming language, one that
is widely used among developers working in that language.
The "System Libraries" of an executable work include anything, other
than the work as a whole, that (a) is included in the normal form of
packaging a Major Component, but which is not part of that Major
Component, and (b) serves only to enable use of the work with that
Major Component, or to implement a Standard Interface for which an
implementation is available to the public in source code form. A
"Major Component", in this context, means a major essential component
(kernel, window system, and so on) of the specific operating system
(if any) on which the executable work runs, or a compiler used to
produce the work, or an object code interpreter used to run it.
The "Corresponding Source" for a work in object code form means all
the source code needed to generate, install, and (for an executable
work) run the object code and to modify the work, including scripts to
control those activities. However, it does not include the work's
System Libraries, or general-purpose tools or generally available free
programs which are used unmodified in performing those activities but
which are not part of the work. For example, Corresponding Source
includes interface definition files associated with source files for
the work, and the source code for shared libraries and dynamically
linked subprograms that the work is specifically designed to require,
such as by intimate data communication or control flow between those
subprograms and other parts of the work.
The Corresponding Source need not include anything that users
can regenerate automatically from other parts of the Corresponding
Source.
The Corresponding Source for a work in source code form is that
same work.
2. Basic Permissions.
All rights granted under this License are granted for the term of
copyright on the Program, and are irrevocable provided the stated
conditions are met. This License explicitly affirms your unlimited
permission to run the unmodified Program. The output from running a
covered work is covered by this License only if the output, given its
content, constitutes a covered work. This License acknowledges your
rights of fair use or other equivalent, as provided by copyright law.
You may make, run and propagate covered works that you do not
convey, without conditions so long as your license otherwise remains
in force. You may convey covered works to others for the sole purpose
of having them make modifications exclusively for you, or provide you
with facilities for running those works, provided that you comply with
the terms of this License in conveying all material for which you do
not control copyright. Those thus making or running the covered works
for you must do so exclusively on your behalf, under your direction
and control, on terms that prohibit them from making any copies of
your copyrighted material outside their relationship with you.
Conveying under any other circumstances is permitted solely under
the conditions stated below. Sublicensing is not allowed; section 10
makes it unnecessary.
3. Protecting Users' Legal Rights From Anti-Circumvention Law.
No covered work shall be deemed part of an effective technological
measure under any applicable law fulfilling obligations under article
11 of the WIPO copyright treaty adopted on 20 December 1996, or
similar laws prohibiting or restricting circumvention of such
measures.
When you convey a covered work, you waive any legal power to forbid
circumvention of technological measures to the extent such circumvention
is effected by exercising rights under this License with respect to
the covered work, and you disclaim any intention to limit operation or
modification of the work as a means of enforcing, against the work's
users, your or third parties' legal rights to forbid circumvention of
technological measures.
4. Conveying Verbatim Copies.
You may convey verbatim copies of the Program's source code as you
receive it, in any medium, provided that you conspicuously and
appropriately publish on each copy an appropriate copyright notice;
keep intact all notices stating that this License and any
non-permissive terms added in accord with section 7 apply to the code;
keep intact all notices of the absence of any warranty; and give all
recipients a copy of this License along with the Program.
You may charge any price or no price for each copy that you convey,
and you may offer support or warranty protection for a fee.
5. Conveying Modified Source Versions.
You may convey a work based on the Program, or the modifications to
produce it from the Program, in the form of source code under the
terms of section 4, provided that you also meet all of these conditions:
a) The work must carry prominent notices stating that you modified
it, and giving a relevant date.
b) The work must carry prominent notices stating that it is
released under this License and any conditions added under section
7. This requirement modifies the requirement in section 4 to
"keep intact all notices".
c) You must license the entire work, as a whole, under this
License to anyone who comes into possession of a copy. This
License will therefore apply, along with any applicable section 7
additional terms, to the whole of the work, and all its parts,
regardless of how they are packaged. This License gives no
permission to license the work in any other way, but it does not
invalidate such permission if you have separately received it.
d) If the work has interactive user interfaces, each must display
Appropriate Legal Notices; however, if the Program has interactive
interfaces that do not display Appropriate Legal Notices, your
work need not make them do so.
A compilation of a covered work with other separate and independent
works, which are not by their nature extensions of the covered work,
and which are not combined with it such as to form a larger program,
in or on a volume of a storage or distribution medium, is called an
"aggregate" if the compilation and its resulting copyright are not
used to limit the access or legal rights of the compilation's users
beyond what the individual works permit. Inclusion of a covered work
in an aggregate does not cause this License to apply to the other
parts of the aggregate.
6. Conveying Non-Source Forms.
You may convey a covered work in object code form under the terms
of sections 4 and 5, provided that you also convey the
machine-readable Corresponding Source under the terms of this License,
in one of these ways:
a) Convey the object code in, or embodied in, a physical product
(including a physical distribution medium), accompanied by the
Corresponding Source fixed on a durable physical medium
customarily used for software interchange.
b) Convey the object code in, or embodied in, a physical product
(including a physical distribution medium), accompanied by a
written offer, valid for at least three years and valid for as
long as you offer spare parts or customer support for that product
model, to give anyone who possesses the object code either (1) a
copy of the Corresponding Source for all the software in the
product that is covered by this License, on a durable physical
medium customarily used for software interchange, for a price no
more than your reasonable cost of physically performing this
conveying of source, or (2) access to copy the
Corresponding Source from a network server at no charge.
c) Convey individual copies of the object code with a copy of the
written offer to provide the Corresponding Source. This
alternative is allowed only occasionally and noncommercially, and
only if you received the object code with such an offer, in accord
with subsection 6b.
d) Convey the object code by offering access from a designated
place (gratis or for a charge), and offer equivalent access to the
Corresponding Source in the same way through the same place at no
further charge. You need not require recipients to copy the
Corresponding Source along with the object code. If the place to
copy the object code is a network server, the Corresponding Source
may be on a different server (operated by you or a third party)
that supports equivalent copying facilities, provided you maintain
clear directions next to the object code saying where to find the
Corresponding Source. Regardless of what server hosts the
Corresponding Source, you remain obligated to ensure that it is
available for as long as needed to satisfy these requirements.
e) Convey the object code using peer-to-peer transmission, provided
you inform other peers where the object code and Corresponding
Source of the work are being offered to the general public at no
charge under subsection 6d.
A separable portion of the object code, whose source code is excluded
from the Corresponding Source as a System Library, need not be
included in conveying the object code work.
A "User Product" is either (1) a "consumer product", which means any
tangible personal property which is normally used for personal, family,
or household purposes, or (2) anything designed or sold for incorporation
into a dwelling. In determining whether a product is a consumer product,
doubtful cases shall be resolved in favor of coverage. For a particular
product received by a particular user, "normally used" refers to a
typical or common use of that class of product, regardless of the status
of the particular user or of the way in which the particular user
actually uses, or expects or is expected to use, the product. A product
is a consumer product regardless of whether the product has substantial
commercial, industrial or non-consumer uses, unless such uses represent
the only significant mode of use of the product.
"Installation Information" for a User Product means any methods,
procedures, authorization keys, or other information required to install
and execute modified versions of a covered work in that User Product from
a modified version of its Corresponding Source. The information must
suffice to ensure that the continued functioning of the modified object
code is in no case prevented or interfered with solely because
modification has been made.
If you convey an object code work under this section in, or with, or
specifically for use in, a User Product, and the conveying occurs as
part of a transaction in which the right of possession and use of the
User Product is transferred to the recipient in perpetuity or for a
fixed term (regardless of how the transaction is characterized), the
Corresponding Source conveyed under this section must be accompanied
by the Installation Information. But this requirement does not apply
if neither you nor any third party retains the ability to install
modified object code on the User Product (for example, the work has
been installed in ROM).
The requirement to provide Installation Information does not include a
requirement to continue to provide support service, warranty, or updates
for a work that has been modified or installed by the recipient, or for
the User Product in which it has been modified or installed. Access to a
network may be denied when the modification itself materially and
adversely affects the operation of the network or violates the rules and
protocols for communication across the network.
Corresponding Source conveyed, and Installation Information provided,
in accord with this section must be in a format that is publicly
documented (and with an implementation available to the public in
source code form), and must require no special password or key for
unpacking, reading or copying.
7. Additional Terms.
"Additional permissions" are terms that supplement the terms of this
License by making exceptions from one or more of its conditions.
Additional permissions that are applicable to the entire Program shall
be treated as though they were included in this License, to the extent
that they are valid under applicable law. If additional permissions
apply only to part of the Program, that part may be used separately
under those permissions, but the entire Program remains governed by
this License without regard to the additional permissions.
When you convey a copy of a covered work, you may at your option
remove any additional permissions from that copy, or from any part of
it. (Additional permissions may be written to require their own
removal in certain cases when you modify the work.) You may place
additional permissions on material, added by you to a covered work,
for which you have or can give appropriate copyright permission.
Notwithstanding any other provision of this License, for material you
add to a covered work, you may (if authorized by the copyright holders of
that material) supplement the terms of this License with terms:
a) Disclaiming warranty or limiting liability differently from the
terms of sections 15 and 16 of this License; or
b) Requiring preservation of specified reasonable legal notices or
author attributions in that material or in the Appropriate Legal
Notices displayed by works containing it; or
c) Prohibiting misrepresentation of the origin of that material, or
requiring that modified versions of such material be marked in
reasonable ways as different from the original version; or
d) Limiting the use for publicity purposes of names of licensors or
authors of the material; or
e) Declining to grant rights under trademark law for use of some
trade names, trademarks, or service marks; or
f) Requiring indemnification of licensors and authors of that
material by anyone who conveys the material (or modified versions of
it) with contractual assumptions of liability to the recipient, for
any liability that these contractual assumptions directly impose on
those licensors and authors.
All other non-permissive additional terms are considered "further
restrictions" within the meaning of section 10. If the Program as you
received it, or any part of it, contains a notice stating that it is
governed by this License along with a term that is a further
restriction, you may remove that term. If a license document contains
a further restriction but permits relicensing or conveying under this
License, you may add to a covered work material governed by the terms
of that license document, provided that the further restriction does
not survive such relicensing or conveying.
If you add terms to a covered work in accord with this section, you
must place, in the relevant source files, a statement of the
additional terms that apply to those files, or a notice indicating
where to find the applicable terms.
Additional terms, permissive or non-permissive, may be stated in the
form of a separately written license, or stated as exceptions;
the above requirements apply either way.
8. Termination.
You may not propagate or modify a covered work except as expressly
provided under this License. Any attempt otherwise to propagate or
modify it is void, and will automatically terminate your rights under
this License (including any patent licenses granted under the third
paragraph of section 11).
However, if you cease all violation of this License, then your
license from a particular copyright holder is reinstated (a)
provisionally, unless and until the copyright holder explicitly and
finally terminates your license, and (b) permanently, if the copyright
holder fails to notify you of the violation by some reasonable means
prior to 60 days after the cessation.
Moreover, your license from a particular copyright holder is
reinstated permanently if the copyright holder notifies you of the
violation by some reasonable means, this is the first time you have
received notice of violation of this License (for any work) from that
copyright holder, and you cure the violation prior to 30 days after
your receipt of the notice.
Termination of your rights under this section does not terminate the
licenses of parties who have received copies or rights from you under
this License. If your rights have been terminated and not permanently
reinstated, you do not qualify to receive new licenses for the same
material under section 10.
9. Acceptance Not Required for Having Copies.
You are not required to accept this License in order to receive or
run a copy of the Program. Ancillary propagation of a covered work
occurring solely as a consequence of using peer-to-peer transmission
to receive a copy likewise does not require acceptance. However,
nothing other than this License grants you permission to propagate or
modify any covered work. These actions infringe copyright if you do
not accept this License. Therefore, by modifying or propagating a
covered work, you indicate your acceptance of this License to do so.
10. Automatic Licensing of Downstream Recipients.
Each time you convey a covered work, the recipient automatically
receives a license from the original licensors, to run, modify and
propagate that work, subject to this License. You are not responsible
for enforcing compliance by third parties with this License.
An "entity transaction" is a transaction transferring control of an
organization, or substantially all assets of one, or subdividing an
organization, or merging organizations. If propagation of a covered
work results from an entity transaction, each party to that
transaction who receives a copy of the work also receives whatever
licenses to the work the party's predecessor in interest had or could
give under the previous paragraph, plus a right to possession of the
Corresponding Source of the work from the predecessor in interest, if
the predecessor has it or can get it with reasonable efforts.
You may not impose any further restrictions on the exercise of the
rights granted or affirmed under this License. For example, you may
not impose a license fee, royalty, or other charge for exercise of
rights granted under this License, and you may not initiate litigation
(including a cross-claim or counterclaim in a lawsuit) alleging that
any patent claim is infringed by making, using, selling, offering for
sale, or importing the Program or any portion of it.
11. Patents.
A "contributor" is a copyright holder who authorizes use under this
License of the Program or a work on which the Program is based. The
work thus licensed is called the contributor's "contributor version".
A contributor's "essential patent claims" are all patent claims
owned or controlled by the contributor, whether already acquired or
hereafter acquired, that would be infringed by some manner, permitted
by this License, of making, using, or selling its contributor version,
but do not include claims that would be infringed only as a
consequence of further modification of the contributor version. For
purposes of this definition, "control" includes the right to grant
patent sublicenses in a manner consistent with the requirements of
this License.
Each contributor grants you a non-exclusive, worldwide, royalty-free
patent license under the contributor's essential patent claims, to
make, use, sell, offer for sale, import and otherwise run, modify and
propagate the contents of its contributor version.
In the following three paragraphs, a "patent license" is any express
agreement or commitment, however denominated, not to enforce a patent
(such as an express permission to practice a patent or covenant not to
sue for patent infringement). To "grant" such a patent license to a
party means to make such an agreement or commitment not to enforce a
patent against the party.
If you convey a covered work, knowingly relying on a patent license,
and the Corresponding Source of the work is not available for anyone
to copy, free of charge and under the terms of this License, through a
publicly available network server or other readily accessible means,
then you must either (1) cause the Corresponding Source to be so
available, or (2) arrange to deprive yourself of the benefit of the
patent license for this particular work, or (3) arrange, in a manner
consistent with the requirements of this License, to extend the patent
license to downstream recipients. "Knowingly relying" means you have
actual knowledge that, but for the patent license, your conveying the
covered work in a country, or your recipient's use of the covered work
in a country, would infringe one or more identifiable patents in that
country that you have reason to believe are valid.
If, pursuant to or in connection with a single transaction or
arrangement, you convey, or propagate by procuring conveyance of, a
covered work, and grant a patent license to some of the parties
receiving the covered work authorizing them to use, propagate, modify
or convey a specific copy of the covered work, then the patent license
you grant is automatically extended to all recipients of the covered
work and works based on it.
A patent license is "discriminatory" if it does not include within
the scope of its coverage, prohibits the exercise of, or is
conditioned on the non-exercise of one or more of the rights that are
specifically granted under this License. You may not convey a covered
work if you are a party to an arrangement with a third party that is
in the business of distributing software, under which you make payment
to the third party based on the extent of your activity of conveying
the work, and under which the third party grants, to any of the
parties who would receive the covered work from you, a discriminatory
patent license (a) in connection with copies of the covered work
conveyed by you (or copies made from those copies), or (b) primarily
for and in connection with specific products or compilations that
contain the covered work, unless you entered into that arrangement,
or that patent license was granted, prior to 28 March 2007.
Nothing in this License shall be construed as excluding or limiting
any implied license or other defenses to infringement that may
otherwise be available to you under applicable patent law.
12. No Surrender of Others' Freedom.
If conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License. If you cannot convey a
covered work so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you may
not convey it at all. For example, if you agree to terms that obligate you
to collect a royalty for further conveying from those to whom you convey
the Program, the only way you could satisfy both those terms and this
License would be to refrain entirely from conveying the Program.
13. Use with the GNU Affero General Public License.
Notwithstanding any other provision of this License, you have
permission to link or combine any covered work with a work licensed
under version 3 of the GNU Affero General Public License into a single
combined work, and to convey the resulting work. The terms of this
License will continue to apply to the part which is the covered work,
but the special requirements of the GNU Affero General Public License,
section 13, concerning interaction through a network will apply to the
combination as such.
14. Revised Versions of this License.
The Free Software Foundation may publish revised and/or new versions of
the GNU General Public License from time to time. Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.
Each version is given a distinguishing version number. If the
Program specifies that a certain numbered version of the GNU General
Public License "or any later version" applies to it, you have the
option of following the terms and conditions either of that numbered
version or of any later version published by the Free Software
Foundation. If the Program does not specify a version number of the
GNU General Public License, you may choose any version ever published
by the Free Software Foundation.
If the Program specifies that a proxy can decide which future
versions of the GNU General Public License can be used, that proxy's
public statement of acceptance of a version permanently authorizes you
to choose that version for the Program.
Later license versions may give you additional or different
permissions. However, no additional obligations are imposed on any
author or copyright holder as a result of your choosing to follow a
later version.
15. Disclaimer of Warranty.
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
16. Limitation of Liability.
IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
17. Interpretation of Sections 15 and 16.
If the disclaimer of warranty and limitation of liability provided
above cannot be given local legal effect according to their terms,
reviewing courts shall apply local law that most closely approximates
an absolute waiver of all civil liability in connection with the
Program, unless a warranty or assumption of liability accompanies a
copy of the Program in return for a fee.
END OF TERMS AND CONDITIONS
How to Apply These Terms to Your New Programs
If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.
To do so, attach the following notices to the program. It is safest
to attach them to the start of each source file to most effectively
state the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.
{one line to give the program's name and a brief idea of what it does.}
Copyright (C) {year} {name of author}
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
Also add information on how to contact you by electronic and paper mail.
If the program does terminal interaction, make it output a short
notice like this when it starts in an interactive mode:
{project} Copyright (C) {year} {fullname}
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License. Of course, your program's commands
might be different; for a GUI interface, you would use an "about box".
You should also get your employer (if you work as a programmer) or school,
if any, to sign a "copyright disclaimer" for the program, if necessary.
For more information on this, and how to apply and follow the GNU GPL, see
<http://www.gnu.org/licenses/>.
The GNU General Public License does not permit incorporating your program
into proprietary programs. If your program is a subroutine library, you
may consider it more useful to permit linking proprietary applications with
the library. If this is what you want to do, use the GNU Lesser General
Public License instead of this License. But first, please read
<http://www.gnu.org/philosophy/why-not-lgpl.html>.
*/


Matrix initialize_trustee_utility(int trustee_guilt)
{
	Matrix ut = Zero_matrix(noa, 5);
	for(Matrix::size_type money_invested = 0; money_invested < ut.size1(); ++money_invested)
	{
		for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
		{
			int money_kept = 5*max_amount - 5*money_invested;
			int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6.0);
			int total_profit_investor = money_kept + money_returned;
			double believed_guilt = static_cast<double>(trustee_guilt);
			int total_profit_trustee = rbf*5*money_invested - money_returned;
			
			ut(money_invested,response) = (total_profit_trustee -  believed_guilt*(0.1*believed_guilt+0.3)  * max(total_profit_trustee - total_profit_investor, 0));			
		}
	}
	
	return ut;
}

Matrix initialize_trustee_probabilities(Matrix const& ut)
{
	Matrix trustee_probabilities = Zero_matrix(noa, 5);
	
	for(Matrix::size_type money_invested = 0; money_invested < trustee_probabilities.size1(); ++money_invested)
	{
		double sum = 0.0;
		for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
		{
			sum += exp(1.0/temperature*ut(money_invested, money_returned));
		}
		
		for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
		{
			trustee_probabilities(money_invested, money_returned) = exp(1.0/temperature*ut(money_invested, money_returned))/sum;
		}
	}
	
	return trustee_probabilities;
}

Matrix initialize_trustee_rollout_likelihood(Matrix const& trustee_probabilities, Index_vector const& max_ut_index)
{
	Matrix trustee_rollout_likelihood = Zero_matrix(noa, 5);
	for(Matrix::size_type money_invested = 0; money_invested < trustee_rollout_likelihood.size1(); ++money_invested)
	{	
		boost::numeric::ublas::matrix_row<Matrix> row(trustee_rollout_likelihood, money_invested);
		greedy_probabilities(row.begin(), row.begin()+nor(money_invested), max_ut_index[money_invested]);
	}
	
	return trustee_rollout_likelihood;
}

Index_vector initialize_max_ut_index(const Matrix& ut)
{
	Index_vector ut_max(noa, 0); //Matrix containing the max utility responses of the trustee to a given offer
	for(Index_vector::size_type money_invested = 0; money_invested < ut_max.size(); ++money_invested)
	{
		double max = 0.0;
		Matrix::size_type max_index = 0;
		for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
		{
			if(max < ut(money_invested, money_returned))
			{
				max = ut(money_invested, money_returned);
				max_index = money_returned;
			}
		}
		ut_max[money_invested] = max_index;
	}
	
	return ut_max;
}

Matrix initialize_offer_utility(Matrix_vector const& investor_choice_likelihood)
{
	Matrix_vector uipt_init(nob, Zero_matrix(noa, 5)); //utility of the investor as perceived by the trustee given a belief 
	for(Matrix_vector::size_type b = 0; b < uipt_init.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < uipt_init[b].size1(); ++money_invested)
		{
			for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
			{
				int money_kept = 5*max_amount - 5*money_invested;
				int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6);
				int total_profit_trustee = rbf *5* money_invested - money_returned;
				int total_profit_investor = money_kept + money_returned;
				double believed_guilt = static_cast<double>(b);
				uipt_init[b](money_invested, response) = (total_profit_investor -  believed_guilt*(0.1*believed_guilt+0.3) * max(total_profit_investor - total_profit_trustee, 0));
			}
		}
	}
	
	Matrix offer_utility = Zero_matrix(noa, nob);
	for(Matrix::size_type investor_guilt = 0; investor_guilt < nob; ++investor_guilt)
	{
		for(Matrix::size_type money_invested = 0; money_invested < noa; ++money_invested)
		{
			for(int trustee_guilt = 0; trustee_guilt < offer_utility.size2(); ++trustee_guilt)
			{
				for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
				{
					offer_utility(money_invested,investor_guilt) += 1.0/(nob) *
					                                                uipt_init[investor_guilt](money_invested,money_returned) *
																	investor_choice_likelihood[trustee_guilt](money_invested,money_returned);
				}
			}
			
		}
	}
	
	return offer_utility;
}

Matrix initialize_trustee_choice_likelihood(Matrix const& offer_utility)
{
	Matrix trustee_choice_likelihood = Zero_matrix(noa, nob);
	for(Matrix::size_type investor_guilt = 0; investor_guilt < trustee_choice_likelihood.size2(); ++investor_guilt)
	{
		double sum = 0.0;
		for(Matrix::size_type money_invested = 0; money_invested < trustee_choice_likelihood.size1(); ++money_invested)
		{
			sum += exp(1.0/temperature*offer_utility(money_invested, investor_guilt));
		}
		
		for(Matrix::size_type money_invested = 0; money_invested < trustee_choice_likelihood.size1(); ++money_invested)
		{
			trustee_choice_likelihood(money_invested, investor_guilt) = exp(1.0/temperature*offer_utility(money_invested, investor_guilt))/sum;
		}
	}
	
	return trustee_choice_likelihood;
}


boost::array<int, global_time_horizon> custom_sort(boost::array<int, global_time_horizon> hist, int time)
{
	boost::array<int, global_time_horizon> sorted_hist;
	for(int ind=0; ind < global_time_horizon; ++ind)
	{	
		sorted_hist[ind]=0;
	}

	boost::array<int, global_time_horizon> calc_hist;	
	for(int ind=0; ind < global_time_horizon; ++ind)
	{
		calc_hist[ind]=hist[ind];
	}	

	int max_ind;
	for(int index = time; 0<=index ; --index)
	{
		for(int run =0; run <= index; ++run) 
		{
			max_ind =(sorted_hist[index] > calc_hist[run] ? max_ind:run);
			sorted_hist[index] = (sorted_hist[index] > calc_hist[run] ? sorted_hist[index]:calc_hist[run]);
		}
		calc_hist[max_ind]=calc_hist[index];
		max_ind=0;
	}
	
	return sorted_hist;
}

int mini(int no_one, int no_two)
{
	int min = ( no_one < no_two ? no_one:no_two);
	return min;
}


Matrix initialize_ui_init(int guilt)
{
	Matrix ui_init = Zero_matrix(noa, 5);
	for(Matrix::size_type money_invested = 0; money_invested < ui_init.size1(); ++money_invested)
	{
		for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
		{
			int money_kept = 5*max_amount - 5*money_invested;
			int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6);
			int total_profit_investor = money_kept + money_returned;
			double believed_guilt = static_cast<double>(guilt);
			int total_profit_trustee = rbf*5*money_invested - money_returned;
			
			ui_init(money_invested,response) = (total_profit_investor -  believed_guilt*(0.1*believed_guilt+0.3)  * max(total_profit_investor - total_profit_trustee, 0));
		}
	}
	
	return ui_init;
}

Matrix_vector initialize_utpi_init()
{
    Matrix_vector utpi_init(nob, Zero_matrix(noa, 5)); //utility of the trustee as perceived by the investor given a belief (either 0 = greedy, or 1 = cooperative)
	for(Matrix_vector::size_type b = 0; b < utpi_init.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < utpi_init[b].size1(); ++money_invested)
		{
			for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
			{
				int money_kept = 5*max_amount - 5*money_invested;
				int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6);
				int total_profit_trustee = rbf * 5*money_invested - money_returned;
				int total_profit_investor = money_kept + money_returned;
				double believed_guilt = static_cast<double>(b);
				utpi_init[b](money_invested, response) = (total_profit_trustee -  believed_guilt*(0.1*believed_guilt+0.3) * max(total_profit_trustee - total_profit_investor, 0));
			}
		}
	}
	
	return utpi_init;
}

Matrix initialize_investor_utility(Matrix const& ui_init, Matrix_vector const& choice_likelihood)
{
	Matrix ui = Zero_matrix(noa, nob);
	for(Matrix_vector::size_type b = 0; b < choice_likelihood.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < choice_likelihood[b].size1(); ++money_invested)
		{
			double max = 0.0;
			Matrix::size_type max_index = 0;
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				ui(money_invested,b) += ui_init(money_invested,money_returned)*choice_likelihood[b](money_invested,money_returned); //expected values
			}
		}
	}
	
	return ui;
}

Matrix_vector initialize_choice_likelihood(const Matrix_vector& utpi_init)
{	
	Matrix_vector choice_likelihood(nob, Zero_matrix(noa, 5)); //describes the likelihood of the trustee to choose a certain response (how much money he returns) as perceived by the investor conditional on belief
	for(Matrix_vector::size_type b = 0; b < choice_likelihood.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < choice_likelihood[b].size1(); ++money_invested)
		{
			double sum = 0.0;
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				sum += exp(1.0/temperature*utpi_init[b](money_invested, money_returned));
			}
			
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				choice_likelihood[b](money_invested, money_returned) = exp(1.0/temperature*utpi_init[b](money_invested, money_returned))/sum;
			}
		}
	}
	
	return choice_likelihood;
}

Index_vector initialize_max_ui_index(const Matrix& ui)
{
	Index_vector max_ui_index(nob,0);
	for(Index_vector::size_type b = 0; b < nob; ++b)
	{
		double max = 0.0;
		Matrix::size_type max_index = 0;
		for(Matrix::size_type money_invested = 0; money_invested < noa; ++money_invested)
		{
			if(max < ui(money_invested, b))
			{
				max = ui(money_invested, b);
				max_index = money_invested;
			}
		}
		max_ui_index[b] = max_index;
	}
	
	return max_ui_index;
}

Matrix initialize_investor_probabilitites(const Index_vector& max_ui_index)
{
	Matrix investor_probabilities = Zero_matrix(nob, noa);
	for(Matrix::size_type b = 0; b < investor_probabilities.size1(); ++b)
	{	
		boost::numeric::ublas::matrix_row<Matrix> row(investor_probabilities, b);
		greedy_probabilities(row.begin(), row.end(), max_ui_index[b]);
	}
	
	return investor_probabilities;
}	

std::vector<double> investor_k( int const& present_time
					 , int const& planning_horizon
					 , boost::array<int,3> guilt_parameter
					 , int const& k1
					 , int const& simulations
					 , boost::array<boost::array<double, nob>, 3> const& belief_parameters
					 , boost::array<int, global_time_horizon> const& pastactions 
					 , boost::array<int, global_time_horizon> const& responses
					 , boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> const& path_numbers
					 , std::vector<double> const& array_pay
					 , boost::array<Matrix, nob> const& ui_init_system
					 , boost::array<Matrix, nob> const& ut_init_system
					 , boost::array<Matrix, nob> const& investor_probabilities_system
					 , boost::array<Matrix, nob> const& trustee_rollout_likelihood_system
					 , Matrix_vector const& investor_choice_likelihood
					 , Matrix const& trustee_choice_likelihood
					 , int factor);



std::vector<double> trustee_k(  int const& money_invested
					, int const& present_time
					, int const& planning_horizon
					, boost::array<int,3> guilt_parameter
					, int const& k2
					, int const& simulations
					, boost::array<boost::array<double, nob>, 3> const& belief_parameters
					, boost::array<int, global_time_horizon> const& pastactions 
					, boost::array<int, global_time_horizon> const& responses
					, boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> const& path_numbers
					, std::vector<double> const& array_pay
					, boost::array<Matrix,nob> const& ui_init_system
					, boost::array<Matrix, nob> const& ut_init_system
					, boost::array<Matrix, nob> const& investor_probabilities_system
					, boost::array<Matrix, nob> const& trustee_rollout_likelihood_system
					, Matrix_vector const& investor_choice_likelihood
					, Matrix const& trustee_choice_likelihood
					, int factor)
{
	
	MEMORY_POOL<True_node> mempool;
	True_node* root = new True_node(); 	
	boost::array<int,global_time_horizon> sorted_hist;
	boost::array<int, global_time_horizon> action;
	boost::array<int, global_time_horizon> response;
	std::vector<double> trustee_payoff (noa,0.0);
	int trustee_guilt = guilt_parameter[k2];	
	for(int t=0; t < global_time_horizon; ++t)
	{
		action[t] = pastactions[t];
	}


	
	for(int t=0; t < global_time_horizon; ++t)
	{
		response[t] = responses[t];
	}
	if( (k2==0) )
	{	
		for(int resp=0; resp < nor(money_invested); ++resp)
		{
			trustee_payoff[resp]=investor_choice_likelihood[trustee_guilt](money_invested, resp);
		}
		delete root;
	}
	else
	{

		True_node* origin = new True_node();
		True_node* current_node;
		True_node* Trustee_node_r;
		origin->set_child(money_invested, root);
		boost::array<int, global_time_horizon> sorted_hist;
		
		boost::array<boost::array<double,nob>,3> initial_beliefs;	
		boost::array<boost::array<double,nob>,3> beliefs;	

		for(unsigned int level=0; level < 3; ++level) 
		{
			for(unsigned int belief=0; belief < nob; ++belief)
			{
				initial_beliefs[level][belief] = belief_parameters[level][belief];
			}
		}
		
		std::vector<double> pay (noa,0.0);				
		boost::array<boost::array<double,noa>,nob> exp_payoffs;
				
		
		boost::array<True_node*,global_time_horizon> path;
		boost::array<double,global_time_horizon> value;
		boost::array<unsigned int, global_time_horizon> action_count;


		
		int last_action;
		int last_response;
		int act;
		int game;
		long long unsigned int summe;
		int max ;
		int old_max;
		long long unsigned int num_act;
		long long unsigned int counter;	
		int unvisited_action;
		int et;		
		boost::array<double,nob> belief_probability;
		double sum =0.0;
		for(int o = 0; o < nob; ++o)
		{
			sum += initial_beliefs[2-k2][o];
		}
		for(int o = 0; o < nob; ++o)
		{
			belief_probability[o] = initial_beliefs[2-k2][o]/sum;
		}
		int trustee_guilt_belief = softmax(belief_probability,17);
			
		path[present_time] = root;
		action[present_time] = money_invested;
		response[present_time]= softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], money_invested),2);
		value[present_time] = ut_init_system[trustee_guilt](action[present_time], response[present_time]);
		root->inc_action_count(response[present_time]);

					
		for(int i = present_time+1; i < planning_horizon; ++i)
		{
			last_action = softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),3);
			last_response = softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], last_action),4);
			value[present_time] += ut_init_system[trustee_guilt](last_action, last_response);
		}
					
		root->rollout_done();

		sum = 0.0;
		for( int i = present_time; i >= present_time; --i)
		{
			sum += value[i];
			path[i]->set_payoff(response[i], path[i]->get_payoff(response[i]) + (sum - path[i]->get_payoff(response[i]) ) / (path[i]->get_action_count(response[i])));
		}

		int local_simulations = simulations;
		
		for(int re=0; re < noa; ++re)	//do normal tree calculation except response is fixed (if available) at 1 of the 5 possible values
		{

			for(int j=0; j < 5*(planning_horizon-present_time+1); ++j) 
			{
			
				for(int level=0; level < 3; ++level)
				{
					for(int belief=0; belief < nob; ++belief)
					{
						beliefs[level][belief] = initial_beliefs[level][belief];
					}
				}
					
				trustee_guilt_belief = softmax(belief_probability,6);		
			
				current_node = origin;
				game = present_time;
				num_act=0;
				summe=0;
				max =0;
				old_max=0;
				
				Trustee_node_r = root;
				
				for(; game < planning_horizon; ++game)
				{
	
					if(!current_node)
					{	
						current_node = new True_node(); 
						Trustee_node_r-> set_child(response[game-1], current_node);					
						if(k2==1)
						{
							summe=0;
							max =0;
							old_max=0;
							num_act=0;
							counter=0;

							if(game>0)
							{
								for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
								{
									sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
								}				
								sorted_hist =custom_sort(sorted_hist, game-1);	
								for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
								{
									if(!(sorted_hist[hist_sum]==0))
									{
										max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
										if(sorted_hist[hist_sum] < old_max)
										{
											cout << "ERROR: sort didn't work" << endl;
										}										
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
										{
											for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
											{
												summe += path_numbers[up][(game)-hist_sum-1];
											}
										}
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
										{
											summe += sorted_hist[hist_sum]-old_max;
										}
										old_max = max;									
									}
								counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
								}
								num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
							}			
							
							for(int belief=0; belief < nob ; ++belief)
							{
								for(int possible_action =0; possible_action < noa; ++possible_action)
								{
									current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief);
								}
							}	
						}
					
						if(k2==2)
						{
							for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
							{
								guilt_parameter[1]=guilt_belief;
								pay = investor_k(game, planning_horizon , guilt_parameter, 1, factor*simulation_iterations/10*(planning_horizon-game), beliefs, action, response,
								path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor);					
								for(int i=0; i <noa ; ++i)
								{
									trustee_payoff[i]=pay[i];
								}						
								for(int possible_action =0; possible_action < noa; ++possible_action)
								{
									current_node->set_exp_payoffs(possible_action,trustee_payoff[possible_action],guilt_belief);
								}							
							}					
						}	
					}
					action[game]=money_invested;
			
					if(k2==0 && game > present_time)
					{
						action[game]= softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),7);
					}
						
						
					if(k2>0 && game >present_time)
					{
						exp_payoffs =current_node->get_exp_payoffs();
						action[game] =  softmax(exp_payoffs[trustee_guilt_belief],8);
					}			

					if(k2==2 && game > present_time) 
					{
						for(int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
						}
					}

					current_node->inc_action_count(action[game]);
					Trustee_node_r = current_node->get_child(action[game]);
					if(!Trustee_node_r)
					{

						Trustee_node_r = new True_node(); 			
						path[game]=Trustee_node_r;
						current_node->set_child(action[game], Trustee_node_r);
			

						response[game]= softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], action[game]),14);
						value[game] = ut_init_system[trustee_guilt](action[game], response[game]);
						for(int i = game + 1; i < planning_horizon; ++i)
						{
							last_action = softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),9);
							last_response = softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], last_action),16);
							value[game] += ut_init_system[trustee_guilt](last_action, last_response);
						}
							
						Trustee_node_r->inc_action_count(response[game]);					
						++game;
						break;		

					}
					else
					{
						if(action[game]==0)
						{
							response[game]=0;
						}
						else
						{

							unvisited_action = Trustee_node_r->get_next_free_child();

							
							if(unvisited_action == noa)
							{
								response[game] = re;
							}
							else
							{
								response[game] = unvisited_action;
							}	

						

						}
						if(k2==1 && !(action[game]==0)) 
						{
							for( int belief=0; belief<nob; ++belief)
							{				
								beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
							}
						}							
						if(k2==2  && !(action[game]==0))
						{
							for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
							{
								beliefs[1][guilt_belief]+=investor_choice_likelihood[guilt_belief](action[game], response[game]);
							}
						}						
						Trustee_node_r->inc_action_count(response[game]);
						value[game] = ut_init_system[trustee_guilt](action[game], response[game]);
						current_node = Trustee_node_r->get_child(response[game]);			
						
					}
					path[game]=Trustee_node_r;
				}
				
				sum = 0.0;
				for( int i = game-1; i >= present_time; --i)
				{
					sum += value[i];
					path[i]->set_payoff(response[i], path[i]->get_payoff(response[i]) + (sum - path[i]->get_payoff(response[i]) ) / (path[i]->get_action_count(response[i])));
				}
			}
		}
		
		for(int iteration = 0; iteration < local_simulations; ++iteration)
		{
			
			for(int level=0; level < 3; ++level)
			{
				for(int belief=0; belief < nob; ++belief)
				{
					beliefs[level][belief] = initial_beliefs[level][belief];
				}
			}
				
			trustee_guilt_belief = softmax(belief_probability,10);		
		
			current_node = origin;
			Trustee_node_r = root;
				
			game = present_time;

			for(; game < planning_horizon; ++game)
			{
	
				if(!current_node)
				{
					current_node = new True_node(); 
					Trustee_node_r-> set_child(response[game-1], current_node);			
					if(k2==1)
					{
						summe=0;
						max =0;
						old_max=0;
						num_act=0;
						counter=0;

						if(game>0)
						{
							for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
							{
								sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
							}				
							sorted_hist =custom_sort(sorted_hist, game-1);	
							for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
							{
								if(!(sorted_hist[hist_sum]==0))
								{
									max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
									if(sorted_hist[hist_sum] < old_max)
									{
										cout << "ERROR: sort didn't work" << endl;
									}										
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
									{
										for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
										{
											summe += path_numbers[up][(game)-hist_sum-1];
										}
									}
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
									{
										summe += sorted_hist[hist_sum]-old_max;
									}
									old_max = max;									
								}
								counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
							}
							num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
						}		
						
						for(int belief=0; belief < nob ; ++belief)
						{
							for(int possible_action =0; possible_action < noa; ++possible_action)
							{
								current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief); //planning horizon can remain
							}
						}	
					}
					
					if(k2==2)
					{
						for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
						{
							guilt_parameter[1]=guilt_belief;
							pay = investor_k(game, planning_horizon , guilt_parameter, 1, factor*simulation_iterations/10*(planning_horizon-game), beliefs, action, response,
							path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor);					
							for(int i=0; i <noa ; ++i)
							{
								trustee_payoff[i]=pay[i];
							}						
							for(int possible_action =0; possible_action < noa; ++possible_action)
							{
								current_node->set_exp_payoffs(possible_action,trustee_payoff[possible_action],guilt_belief);
							}							
						}					
					}	
				}			
				
				action[game]=money_invested;
		
				if(k2==0 && game > present_time)
				{
					action[game]=  softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),11);
				}
					
					
				if(k2>0 && game >present_time)
				{
					exp_payoffs =current_node->get_exp_payoffs();
					action[game] =  softmax(exp_payoffs[trustee_guilt_belief],12);
				}						
				if(k2==2 && game > present_time) 
				{
					for(int belief=0; belief<nob; ++belief)
					{				
						beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
					}
				}										

				current_node->inc_action_count(action[game]);
				Trustee_node_r = current_node->get_child(action[game]);
				if(!Trustee_node_r)
				{

					et = nor(action[game]);
					Trustee_node_r = new True_node(); 			
					path[game]=Trustee_node_r;
					current_node->set_child(action[game], Trustee_node_r);			

					response[game]=softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], action[game]),14);
					value[game] = ut_init_system[trustee_guilt](action[game], response[game]);	
					for(int i = game + 1; i < planning_horizon; ++i)
					{
						last_action = softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),15);
						last_response = softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], last_action),16);
						value[game] += ut_init_system[trustee_guilt](last_action, last_response);
					}
						
					Trustee_node_r->inc_action_count(response[game]);
					Trustee_node_r->rollout_done();
					++game;
					break;		

				}
				else
				{
					if(action[game]==0)
					{
						response[game]=0;
					}
					else
					{
						unvisited_action = Trustee_node_r->get_next_free_child();
						
						if(unvisited_action == noa)
						{
							response[game] = Trustee_node_r->get_next_exploration( game == present_time ? (iteration+5*(planning_horizon-present_time+1)+1) : (current_node->get_action_count(action[game])) );
						}
						else
						{
							response[game] = unvisited_action;
						}						

					}
					if(k2==1  && !(action[game]==0)) 
					{
						for(int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
						}
					}							
					if(k2==2   && !(action[game]==0))
					{
						for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
						{
							beliefs[1][guilt_belief]+=investor_choice_likelihood[guilt_belief](action[game], response[game]);
						}
					}								
					Trustee_node_r->inc_action_count(response[game]);
					value[game] = ut_init_system[trustee_guilt](action[game], response[game]);
					current_node = Trustee_node_r->get_child(response[game]);			
						
				}
				path[game]=Trustee_node_r;
						
			}
					
			sum = 0.0;
			for( int i = game-1; i >= present_time; --i)
			{
				sum += value[i];
				path[i]->set_payoff(response[i], path[i]->get_payoff(response[i]) + (sum - path[i]->get_payoff(response[i]) ) / (path[i]->get_action_count(response[i])));
			}
		}
		sum =0.0;
		for(int i =0; i<nor(money_invested); ++i)
		{
			trustee_payoff[i] = exp(1.0/temperature*(root-> get_payoff(i)));
			sum += trustee_payoff[i];
		}
		for(int i =0; i<nor(money_invested); ++i)
		{
			trustee_payoff[i] = trustee_payoff[i]/sum;
		}	
		delete origin;
	}
	mempool.DeleteAll();	
	return trustee_payoff;
}

std::vector<double> investor_k( int const& present_time
					 , int const& planning_horizon
					 , boost::array<int,3> guilt_parameter
					 , int const& k1
					 , int const& simulations
					 , boost::array<boost::array<double, nob>, 3> const& belief_parameters
					 , boost::array<int, global_time_horizon> const& pastactions 
					 , boost::array<int, global_time_horizon> const& responses
					 , boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> const& path_numbers
					 , std::vector<double> const& array_pay
					 , boost::array<Matrix, nob> const& ui_init_system
					 , boost::array<Matrix, nob> const& ut_init_system
					 , boost::array<Matrix, nob> const& investor_probabilities_system
					 , boost::array<Matrix, nob> const& trustee_rollout_likelihood_system
					 , Matrix_vector const& investor_choice_likelihood
					 , Matrix const& trustee_choice_likelihood
					 , int factor)
{	
	MEMORY_POOL<True_node> mempool;
	True_node* root = new True_node();
	std::vector<double> investor_payoff (noa,0.0);
	boost::array<int, global_time_horizon> action;
	boost::array<int, global_time_horizon> response;
	boost::array<int, global_time_horizon> sorted_hist;		
	int investor_guilt = guilt_parameter[k1];
		//prepare action
	for(int l=0; l < global_time_horizon; ++l)
	{
		action[l]=pastactions[l];
	}
		//prepare response
	for(int l=0; l < global_time_horizon; ++l)
	{
		response[l]=responses[l];
	}		
	if((k1==0) )
	{
		long long unsigned int summe=0;
		int max =0;
		int old_max=0;
		long long unsigned int num_act=0;
		int game = present_time;
		long long unsigned int counter=0;

		if(game>0)
		{
			for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
			{
				sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
			}				
			sorted_hist =custom_sort(sorted_hist, game-1);	
			for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
			{
				if(!(sorted_hist[hist_sum]==0))
				{
					max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
					if(sorted_hist[hist_sum] < old_max)
					{
						cout << "ERROR: sort didn't work" << endl;
					}										
					if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
					{
						for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
						{
							summe += path_numbers[up][(game)-hist_sum-1];
						}
					}
					if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
					{
						summe += sorted_hist[hist_sum]-old_max;
					}
					old_max = max;									
				}
				counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); 							
			}
			num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
		}		
		
		for(int act=0; act < noa; ++act)
		{
			investor_payoff[act] = array_pay[num_act + investor_guilt*noa + (planning_horizon-game-1)*noa*nob+act];
		}
		
		delete root;
	}
	else
	{
		std::vector<double> pay (noa,0.0);
	

		True_node* current_node;
		True_node* Trustee_node_r;
	
		int max_level =2;
		boost::array<boost::array<double,nob>,3> initial_beliefs;	
		boost::array<boost::array<double,nob>,3> beliefs;	

		for(unsigned int level=0; level < 3; ++level)  //level 2 uses everything
		{
			for(unsigned int belief=0; belief < nob; ++belief)
			{
				initial_beliefs[level][belief] = belief_parameters[level][belief];
			}
		}
			
	
		boost::array<True_node*,global_time_horizon> path;
		boost::array<double,global_time_horizon> value;
		boost::array<unsigned int, global_time_horizon> action_count;
		
		int game;
		int last_action;
		int last_response;
		int act;
		long long unsigned int summe;
		int max;
		int old_max;
		long long unsigned int num_act;
		long long unsigned int counter;
		int et;
		int unvisited_action;
		boost::array<boost::array<double,noa>,nob> exp_payoffs;		

		boost::array<double,nob> belief_probability;
		double sum =0.0;
		for(int o = 0; o < nob; ++o)
		{
			sum += initial_beliefs[2-k1][o];
		}
		for(int o = 0; o < nob; ++o)
		{
			belief_probability[o] = initial_beliefs[2-k1][o]/sum;			
		}
		int trustee_guilt_belief = softmax(belief_probability,17);
		

		
		path[present_time] = root;
		action[present_time] = softmax(row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),18);
		value[present_time] = ui_init_system[investor_guilt](action[present_time], softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[present_time]),19));
		root->inc_action_count(action[present_time]);
				
		for(int i = present_time+1; i < planning_horizon; ++i)
		{
			last_action = softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),20);
			last_response = softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], last_action),21);
			value[present_time] += ui_init_system[investor_guilt](last_action, last_response);
		}

		sum = 0.0;
		for( int i = present_time; i >= present_time; --i)
		{
			sum += value[i];
			path[i]->set_payoff(action[i], path[i]->get_payoff(action[i]) + (sum - path[i]->get_payoff(action[i]) ) / (path[i]->get_action_count(action[i])));
		}

		int local_simulations = simulations;
		boost::array<boost::array<double, noa>, nob> inv_exp_payoffs;	
		
		for(int ac= 0; ac < noa; ++ac)	
		{

			for(int j=0; j < 5*(planning_horizon-present_time+1); ++j) 
			{
			
				for(int level=0; level < 3; ++level)
				{
					for(int belief=0; belief < nob; ++belief)
					{
						beliefs[level][belief] = initial_beliefs[level][belief];
					}
				}
								
				trustee_guilt_belief = softmax(belief_probability,22);		
		
				current_node = root;
				
				game = present_time;
				for(; game < planning_horizon; ++game)
				{
					if(!current_node)
					{		
						current_node = new True_node();
						Trustee_node_r-> set_child(response[game-1], current_node);
						path[game] = current_node;
						action[game] = softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),90);
						value[game] = ui_init_system[investor_guilt](action[game], softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),23));
						current_node->inc_action_count(action[game]);
						
						for(int i = game + 1; i < planning_horizon; ++i)
						{
							last_action =softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),95);
							last_response = softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], last_action),24);
							value[game] += ui_init_system[investor_guilt](last_action, last_response);
						}					
						++game;
						break;
					}

					path[game] = current_node;		
					
					if(!(current_node->is_rolled_out()))
					{
						if(k1>1)
						{
							summe=0;
							max =0;
							old_max=0;
							num_act=0;
							counter=0;

							if(game>0)
							{
								for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
								{
									sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
								}				
								sorted_hist =custom_sort(sorted_hist, game-1);	
								for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
								{
									if(!(sorted_hist[hist_sum]==0))
									{
										max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
										if(sorted_hist[hist_sum] < old_max)
										{
											cout << "ERROR: sort didn't work" << endl;
										}										
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
										{
											for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
											{
												summe += path_numbers[up][(game)-hist_sum-1];
											}
										}
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
										{
											summe += sorted_hist[hist_sum]-old_max;
										}
										old_max = max;									
									}
									counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
								}
								num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
							}			
						
							for(int belief=0; belief < nob ; ++belief)
							{
								for(int possible_action =0; possible_action < noa; ++possible_action)
								{
									current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief);
								}
							}	
						}
						current_node-> rollout_done();
					}					

					int unvisited_action = current_node->get_next_free_child();				
					
					if(unvisited_action == noa)
					{
						action[game] = ac;
					}
					else
					{
						action[game] = unvisited_action;
					}
				
					if(k1==1) 
					{
						for(int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
						}
					}		

					if(k1>1)
					{
						exp_payoffs =current_node->get_exp_payoffs();
						for(int belief=0; belief<nob; ++belief)
						{
							beliefs[1][belief] += exp_payoffs[belief][action[game]]; 
						}
					}
					et = nor(action[game]);
		
					current_node->inc_action_count(action[game]);
					Trustee_node_r = current_node->get_child(action[game]);
					if(!Trustee_node_r)
					{
						Trustee_node_r = new True_node(); 

						current_node->set_child(action[game], Trustee_node_r);
						if(k1>0 && !(action[game]==0))
						{

							
							for(int guilt=0; guilt < nob; ++guilt)
							{
								guilt_parameter[k1-1] = guilt;
								pay = trustee_k( action[game], game, planning_horizon, guilt_parameter ,k1-1, factor*simulation_iterations/10*(planning_horizon-game), beliefs , action, response,
								path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor); //only calc trustee, include inf in trustee

								for(int i=0; i < noa; ++i)
								{	

									inv_exp_payoffs[guilt][i] =pay[i];
								}								
								for( int action_loc = 0; action_loc < noa; ++action_loc)
								{
									Trustee_node_r->set_exp_payoffs(action_loc,inv_exp_payoffs[guilt][action_loc],guilt);
								}							
								
							}	
						}
						
					}

					if(k1>0 && !(action[game]==0))
					{
						exp_payoffs =Trustee_node_r->get_exp_payoffs();
						response[game] = softmax(exp_payoffs[trustee_guilt_belief],25);
					}
					else
					{
						response[game]= (action[game]==0 ? 0 :  softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),26));
					}
					Trustee_node_r->inc_action_count(response[game]);
					
					if(k1==2  && !(action[game]==0) ) 
					{
						for( int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
						}
					}			

					value[game] = ui_init_system[investor_guilt](action[game], response[game]);

					current_node = Trustee_node_r->get_child(response[game]);			
				
				}
				sum = 0.0;
				for( int i = game-1; i >= present_time; --i)
				{
					sum += value[i];
					path[i]->set_payoff(action[i], path[i]->get_payoff(action[i]) + (sum - path[i]->get_payoff(action[i]) ) / (path[i]->get_action_count(action[i])));
				}
				
			}		
			
		}
		
		for(unsigned int iteration = 0; iteration < local_simulations; ++iteration)
		{
		
			for(int level=0; level < 3; ++level)
			{
				for(int belief=0; belief < nob; ++belief)
				{
					beliefs[level][belief] = initial_beliefs[level][belief];
				}
			}

			trustee_guilt_belief = softmax(belief_probability,27);		
	
			current_node = root;
			
			game = present_time;
			for(; game < planning_horizon; ++game)
			{

				if(!current_node)
				{		
					current_node = new True_node();
					Trustee_node_r-> set_child(response[game-1], current_node);
					path[game] = current_node;
					action[game] = softmax(row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),28); 
					value[game] = ui_init_system[investor_guilt](action[game], softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),29));
					current_node->inc_action_count(action[game]);

					for(int i = game + 1; i < planning_horizon; ++i)
					{
						last_action = softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),30);
						last_response = softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], last_action),31);
						value[game] += ui_init_system[investor_guilt](last_action, last_response);
					}					
				
					++game;
					break;
				}

				path[game] = current_node;		

					if(k1>1 && !(current_node->is_rolled_out()))
					{
						summe=0;
						max =0;
						old_max=0;
						num_act=0;
						counter=0;

						if(game>0)
						{
							for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
							{
								sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
							}				
							sorted_hist =custom_sort(sorted_hist, game-1);	
							for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
							{
								if(!(sorted_hist[hist_sum]==0))
								{
									max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
									if(sorted_hist[hist_sum] < old_max)
									{
										cout << "ERROR: sort didn't work" << endl;
									}										
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
									{
										for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
										{
											summe += path_numbers[up][(game)-hist_sum-1];
										}
									}
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
									{
										summe += sorted_hist[hist_sum]-old_max;
									}
									old_max = max;									
								}
								counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
							}
							num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
						}		
						
						for(int belief=0; belief < nob ; ++belief)
						{
							for(int possible_action =0; possible_action < noa; ++possible_action)
							{
								current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief);
							}
						}	
						current_node->rollout_done();						
					}	
				
				unvisited_action = current_node->get_next_free_child();
				
			
				if(unvisited_action == noa)
				{
					action[game] = current_node-> get_next_exploration( game == present_time ? iteration+5*(planning_horizon-present_time+1)+1 : (Trustee_node_r->get_action_count(response[game-1])) );

				}
				else
				{
					action[game] = unvisited_action;
				}
				
				if(k1==1) 
				{
					for(int belief=0; belief<nob; ++belief)
					{				
						beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
					}
				}					

				if(k1==2)
				{
					exp_payoffs =current_node->get_exp_payoffs();
					for(int belief=0; belief<nob; ++belief)
					{
						beliefs[1][belief]+= exp_payoffs[belief][action[game]]; 
					}
				}
				et = nor(action[game]);
	
				current_node->inc_action_count(action[game]);
				Trustee_node_r = current_node->get_child(action[game]);
				if(!Trustee_node_r)
				{
	
					Trustee_node_r = new True_node(); 
					current_node->set_child(action[game], Trustee_node_r);
					if(k1>0 &&!(action[game]==0))
					{	
							
						for(int guilt=0; guilt < nob; ++guilt)
						{
							guilt_parameter[1] =guilt;
							pay = trustee_k( action[game], game, planning_horizon, guilt_parameter ,1, factor*simulation_iterations/10*(planning_horizon-game), beliefs , action, response,
							path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor); //only calc trustee, include inf in trustee
							for(int i=0; i <noa; ++i)
							{
								inv_exp_payoffs[guilt][i] =pay[i];
							}							
							for(int action_loc = 0; action_loc < noa; ++action_loc)
							{
								Trustee_node_r->set_exp_payoffs(action_loc,inv_exp_payoffs[guilt][action_loc],guilt);
							}																
						}										
					}
					
				}

				if(k1>0 && !(action[game]==0))
				{
					exp_payoffs =Trustee_node_r->get_exp_payoffs();
					response[game] = softmax(exp_payoffs[trustee_guilt_belief],33);
				}
				else
				{
					response[game]= (action[game]==0 ? 0 :  softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),34));
				}
				Trustee_node_r->inc_action_count(response[game]);
				
				if(k1==2  && !(action[game]==0)) 
				{
					for(int belief=0; belief<nob; ++belief)
					{				
						beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
					}
				}			

				value[game] = ui_init_system[investor_guilt](action[game], response[game]);

				current_node = Trustee_node_r->get_child(response[game]);			
			
			}

			sum = 0.0;
			for( int i = game-1; i >= present_time; --i)
			{
				sum += value[i];
				path[i]->set_payoff(action[i], path[i]->get_payoff(action[i]) + (sum - path[i]->get_payoff(action[i]) ) / (path[i]->get_action_count(action[i])));
			}
			
		}
		
		sum =0.0;
		for(int i =0; i<noa; ++i)
		{		
			investor_payoff[i] = exp(1.0/temperature*(root-> get_payoff(i)));		
			sum += investor_payoff[i];
		}
		for(int i =0; i<noa; ++i)
		{
			investor_payoff[i] = investor_payoff[i]/sum;		
		}	
	delete root;
	}
	mempool.DeleteAll();
	return investor_payoff;
}




int main(int argc, char* argv[])
{	

	static std::vector<double> array_pay(302401125,0.0);
	boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> path_numbers;
	boost::array<boost::array<int, global_time_horizon>,ActionResponsePairs+1> correction_factors;		
			
	int count=0;	
	int ncount=0; 
	path_numbers[0][0]=1;
	path_numbers[0][1]=ActionResponsePairs;
	for(int act=0; act<ActionResponsePairs; ++act)
	{
		correction_factors[act][0] = -act;
	}	
		
	for(int act=1; act<ActionResponsePairs; ++act)
	{
		path_numbers[act][1]= path_numbers[0][1] +correction_factors[act][0];
		count +=path_numbers[act][1];	
		ncount -= path_numbers[act-1][1];
		correction_factors[act][1] = ncount;	
	}
		
	if(global_time_horizon>1)
	{
		path_numbers[0][2]= path_numbers[0][1]+ count;
		correction_factors[0][1]=0;
	}

	for(int t =1; t < (global_time_horizon-1); ++t)
	{	
		count=0;
		ncount=0;	
		for(int act=1; act<ActionResponsePairs; ++act)
		{
			path_numbers[act][t+1]= path_numbers[0][t+1] +correction_factors[act][t];
			count +=path_numbers[act][t+1];	
			ncount -= path_numbers[act-1][t+1];
			correction_factors[act][t+1] = ncount;
			correction_factors[act][t+1] = ncount;
		}
		path_numbers[0][t+2] = path_numbers[0][t+1]+count;
		correction_factors[0][t+1]=0;	
	}					
		
	ifstream infile ("saved_0_3_investor_high_large.bin", ios::in | ios::binary);//|ios::ate);
	infile.seekg (0, ios::beg);	
	char * memblock;
	memblock= new char[1209604504];		
	ifstream::pos_type it =0;
	double store =0.0;
	long long unsigned int tick=0;

	infile.read( memblock,1209604504);	
	it=0;
	for(int t = -1; t <= global_time_horizon-2; ++t) 
	{	
		for(int paths = 1; paths <= path_numbers[0][t+1]; ++paths)
		{	
			for(int y=0; y < (global_time_horizon-t-1);++y) 
			{
				for(int belief=0; belief < nob; ++belief) 
				{			
					for(int action= 0; action < noa; ++ action)	
					{	
						store = *(double*)&memblock[it];
						array_pay[tick]=store; //fill in action likelihood
						it += 8;
						if(static_cast<int>(it) == 1209604504)
						{
							infile.seekg(it);
							infile.read(memblock,1209604446);
							it=0;
						}
						++tick;						
					}
				}	
			}		
		}			
	}
	infile.close();	
		
	delete[] memblock;	

	boost::array<double,noa>  investor_payoff;
	boost::array<double,noa>  trustee_payoff;	
	double sum =0.0;

	int d1;
	int d2;
	int no_sub;
	int start_id =0;
	int end_id;
	int plan;
	int condition;
	
	cout << "Enter Accuracy Condition (0 = discrepancy table calculation, 1 = million path converged example): ";
	cin >> condition;	

	boost::array<int,global_time_horizon> sorted_hist;
	static boost::array<boost::array<boost::array<int,global_time_horizon>,2>, 8100> Subject_Games;
	static boost::array<boost::array<int,2>,8100> Subject_Guilt;
	static boost::array<boost::array<int,2>,8100> Subject_ToM;
	static boost::array<boost::array<int,2>,8100> Subject_Planning;
	
	if(condition == 0)
	{
		cout << "Enter number of simulated subjects: ";
		cin >> no_sub;

		cout << "Enter planning horizon of interest (Integer, 2 to 9): ";
		cin >> plan;	

		for(int sub_id=0; sub_id < no_sub; ++sub_id)
		{
			Subject_Guilt[sub_id][0] = 2;	
			Subject_Planning[sub_id][0] = plan;	
			Subject_ToM[sub_id][0] = 2;
			Subject_Guilt[sub_id][1] = 0;
			Subject_Planning[sub_id][1] = 0;
			Subject_ToM[sub_id][1] = 0;			
		}		
		
		end_id = no_sub;
	}
	else
	{
		no_sub=7;
		for(int sub_id=0; sub_id < no_sub; ++sub_id)
		{
			Subject_Guilt[sub_id][0] = 2;	
			Subject_Planning[sub_id][0] = sub_id+2;	
			Subject_ToM[sub_id][0] = 2;
			Subject_Guilt[sub_id][1] = 0;
			Subject_Planning[sub_id][1] = 0;
			Subject_ToM[sub_id][1] = 0;			
		}			
		end_id=7;
	}
		
	
	boost::array<boost::array<double, nob>, 3> trustee_belief_parameters;	
	boost::array<boost::array<double, nob>, 3> investor_belief_parameters;

	int investor_planning;
	int trustee_planning;
	int WI_ToM;
	int WI_G;
	int WI_P;
	int WT_ToM;
	int WT_G;
	int WT_P;
	double Tlike_max;
	double Ilike_max;
	double like=0.0;
	double Tlike=0.0;
	int k1;
	int k2;	
	double expectation;
	int game;
	long long unsigned int summe;
	int max;
	int old_max;
	long long unsigned int num_act;
	long long unsigned int counter;	
	std::vector<double> holder(noa,0.0);
	boost::array<double,nob> probabilities;	
	Matrix ui_init;
	Matrix_vector utpi_init;
	Matrix_vector investor_choice_likelihood;
	Matrix ui;
	Index_vector max_ui_index;
	Matrix investor_probabilities;
	Matrix ut_init;
	Matrix offer_utility;
	Matrix trustee_choice_likelihood;
	Index_vector max_ut_index;
	Matrix trustee_probabilities;
	Matrix trustee_rollout_likelihood;
	boost::array<int, 3> guilt_parameter;
	boost::array<Matrix, nob> ui_init_system;	
	boost::array<Matrix, nob> investor_probabilities_system;	
	int start;
	for(int system=0; system < nob; ++system)
	{ 
		ui_init_system[system] = initialize_ui_init(system);
		ui = initialize_investor_utility(ui_init_system[system], investor_choice_likelihood);
		max_ui_index = initialize_max_ui_index(ui);
		investor_probabilities_system[system] = initialize_investor_probabilitites(max_ui_index); 		
	}				
	utpi_init = initialize_utpi_init();
	investor_choice_likelihood = initialize_choice_likelihood(utpi_init);	
	boost::array<Matrix, nob> ut_init_system;
	boost::array<Matrix,nob> trustee_rollout_likelihood_system;
	for(int system=0; system < nob; ++system)
	{ 
		ut_init_system[system] = initialize_trustee_utility(system);
		max_ut_index=initialize_max_ut_index(ut_init_system[system]);	
		trustee_probabilities=initialize_trustee_probabilities(ut_init_system[system]);	
		trustee_rollout_likelihood_system[system] =initialize_trustee_rollout_likelihood(trustee_probabilities, max_ut_index);		
	}		
	offer_utility=initialize_offer_utility(investor_choice_likelihood);
	trustee_choice_likelihood = initialize_trustee_choice_likelihood(offer_utility);	

	char OutputFile[40];
	char stra[80];
	
	cout << "Enter the accuracy & speed data output filename (no more than 20 characters): ";
	cin >> OutputFile;	
	strcpy (stra, OutputFile);
	strcat (stra, ".bin");	

	boost::array<boost::array<boost::array<double, nob>, 3>,global_time_horizon> store_trustee_belief_parameters;	
	boost::array<boost::array<boost::array<double, nob>, 3>,global_time_horizon> store_investor_belief_parameters;	

	ofstream ofs(stra, ofstream::out | ofstream::binary);	
	int iteration = 1;
	boost::array<int,8> multiplier;
	if(condition==0)
	{
		multiplier[0]=1;
		multiplier[1]=2;
		multiplier[2]=3;
		multiplier[3]=4;
		multiplier[4]=5;
		multiplier[5]=6;
		multiplier[6]=10;
		multiplier[7]=20;
	}
	else
	{
		iteration=8;
		multiplier[7]=400;
	}
	clock_t stop;	
	boost::array<double, 8100> calculationtime;	
	for(iteration; iteration < 9; ++iteration)
	{
		for(int sub_id= start_id; sub_id < end_id; ++sub_id)
		{
			//cout << sub_id <<endl;

			Tlike_max=1000.0;
			Ilike_max=1000.0;	

			d1 = Subject_Planning[sub_id][0];
			d2 = Subject_Planning[sub_id][1];
			like=0.0;
			Tlike =0.0;	
			for(int level=0; level < 3; ++level)  
			{
				for(int belief=0; belief < nob; ++belief)
				{
					investor_belief_parameters[level][belief] = 1.0;
					for(int time_step=0; time_step < global_time_horizon; ++time_step)
					{							
						store_investor_belief_parameters[time_step][level][belief]=investor_belief_parameters[level][belief];
					}
				}
			}
			for(int level=0; level < 3; ++level)  
			{
				for(int belief=0; belief < nob; ++belief)
				{
					trustee_belief_parameters[level][belief] = 1.0;
					for(int time_step=0; time_step < global_time_horizon; ++time_step)
					{							
						store_trustee_belief_parameters[time_step][level][belief]=trustee_belief_parameters[level][belief];	
					}
				}
			}	

			for(int time_step=0; time_step < 1; ++time_step)
			{
				if(time_step==0)
				{
					stop = clock();	
				}				
				investor_planning = mini(time_step+d1+1, global_time_horizon);	
				trustee_planning= mini(time_step+d2+1, global_time_horizon);
				guilt_parameter[Subject_ToM[sub_id][0]]=Subject_Guilt[sub_id][0];	
				holder = investor_k( time_step, investor_planning , guilt_parameter, Subject_ToM[sub_id][0], multiplier[iteration-1]*simulation_iterations/10*(investor_planning-time_step), investor_belief_parameters, Subject_Games[sub_id][0], Subject_Games[sub_id][1],
				path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, multiplier[(iteration-1)]);			
				for(int i=0; i <noa ; ++i)
				{
					ofs.write( reinterpret_cast<char*>( &holder[i] ), sizeof holder[i] );	
					//cout << holder[i] << endl;
					investor_payoff[i]=holder[i];
					//cout << investor_payoff[i] << endl;
				}
				if(time_step==0)
				{
					stop = clock() -stop;
					calculationtime[sub_id] = ((double) stop)/CLOCKS_PER_SEC;
				}					
				Subject_Games[sub_id][0][time_step]=softmax(investor_payoff,80);							

				if(Subject_ToM[sub_id][1]==0)
				{
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{	
						trustee_belief_parameters[2][guilt_belief]+=trustee_choice_likelihood(Subject_Games[sub_id][0][time_step], guilt_belief);
					}
				}
			
				if(Subject_ToM[sub_id][1]==1)
				{

					game = time_step;
					summe=0;
					max =0;
					old_max=0;
					num_act=0;
					counter=0;
					if(game>0)
					{
						for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
						{
							sorted_hist[hist_sum]=(Subject_Games[sub_id][0][hist_sum]==0 ? 0:((Subject_Games[sub_id][0][hist_sum]-1)*noa + 1 +Subject_Games[sub_id][1][hist_sum]));
						}				
						sorted_hist =custom_sort(sorted_hist, game-1);	
						for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
						{
							if(!(sorted_hist[hist_sum]==0))
							{
								max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
								if(sorted_hist[hist_sum] < old_max)
								{
									cout << "ERROR: sort didn't work" << endl;
								}										
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
								{
									for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
									{
										summe += path_numbers[up][(game)-hist_sum-1];
									}
								}
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
								{
									summe += sorted_hist[hist_sum]-old_max;
								}
								old_max = max;									
							}
							counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
						}
						num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));	
					}
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{
						trustee_belief_parameters[1][guilt_belief]+=array_pay[num_act + guilt_belief*noa + (trustee_planning-game-1)*noa*nob+Subject_Games[sub_id][0][time_step]];				
					}
				}

				if(Subject_ToM[sub_id][0]==2)
				{
					game = time_step;
					summe=0;
					max =0;
					old_max=0;
					num_act=0;
					counter=0;
					if(game>0)
					{
						for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
						{
							sorted_hist[hist_sum]=(Subject_Games[sub_id][0][hist_sum]==0 ? 0:((Subject_Games[sub_id][0][hist_sum]-1)*noa + 1 +Subject_Games[sub_id][1][hist_sum]));
						}				
						sorted_hist =custom_sort(sorted_hist, game-1);	
						for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
						{
							if(!(sorted_hist[hist_sum]==0))
							{
								max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
								if(sorted_hist[hist_sum] < old_max)
								{
									cout << "ERROR: sort didn't work" << endl;
								}										
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
								{
									for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
									{
										summe += path_numbers[up][(game)-hist_sum-1];
									}
								}
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
								{
									summe += sorted_hist[hist_sum]-old_max;
								}
								old_max = max;									
							}
							counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
						}
						num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));	
					}
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{
						investor_belief_parameters[1][guilt_belief]+=array_pay[num_act + guilt_belief*noa + (investor_planning-game-1)*noa*nob+Subject_Games[sub_id][0][time_step]];								
					}		
				}
				if((Subject_Games[sub_id][0][time_step]==0))
				{
					Subject_Games[sub_id][1][time_step]=0;
				}
				if(!(Subject_Games[sub_id][0][time_step]==0))
				{
					sum =0.0;
					guilt_parameter[Subject_ToM[sub_id][1]]=Subject_Guilt[sub_id][1];
					holder = trustee_k( Subject_Games[sub_id][0][time_step],time_step, trustee_planning, guilt_parameter, Subject_ToM[sub_id][1], multiplier[iteration-1]*simulation_iterations/10*(trustee_planning-time_step), trustee_belief_parameters, 
					Subject_Games[sub_id][0], Subject_Games[sub_id][1], path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, multiplier[(iteration-1)]);
					for(int i=0; i <noa ; ++i)
					{							
						trustee_payoff[i]=holder[i];
					}

					Subject_Games[sub_id][1][time_step]=softmax(trustee_payoff,85);
				}
				if(!(Subject_Games[sub_id][0][time_step]==0))
				{						

					if(Subject_ToM[sub_id][0] ==2)
					{

						for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
						{
							guilt_parameter[1]=guilt_belief;
							holder = trustee_k(Subject_Games[sub_id][0][time_step],time_step, investor_planning, guilt_parameter, 1, multiplier[iteration-1]*simulation_iterations/10*(investor_planning-time_step), investor_belief_parameters,
							Subject_Games[sub_id][0], Subject_Games[sub_id][1], path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, multiplier[(iteration-1)]);
							for(int i=0; i <noa ; ++i)
							{									
								trustee_payoff[i]=holder[i];
							}
							investor_belief_parameters[0][guilt_belief] += trustee_payoff[Subject_Games[sub_id][1][time_step]];										
						}
					}
				}
				
				if( Subject_ToM[sub_id][0]==0  && !(Subject_Games[sub_id][0][time_step]==0))
				{
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{		
						investor_belief_parameters[2][guilt_belief]+=investor_choice_likelihood[guilt_belief](Subject_Games[sub_id][0][time_step], Subject_Games[sub_id][1][time_step]);
					}
				}						

				
				if(Subject_ToM[sub_id][1]==1  && !(Subject_Games[sub_id][0][time_step]==0))
				{

					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{			
						trustee_belief_parameters[2][guilt_belief] +=investor_choice_likelihood[guilt_belief](Subject_Games[sub_id][0][time_step], Subject_Games[sub_id][1][time_step]);
					}
				}
		
				if(Subject_ToM[sub_id][0] ==2  && !(Subject_Games[sub_id][0][time_step]==0))
				{
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{			
						investor_belief_parameters[2][guilt_belief]+=investor_choice_likelihood[guilt_belief](Subject_Games[sub_id][0][time_step], Subject_Games[sub_id][1][time_step]);
					}								
				}

				for(int level=0; level < 3; ++level)  
				{
					for(int belief=0; belief < nob; ++belief)
					{					
						store_investor_belief_parameters[time_step][level][belief]=investor_belief_parameters[level][belief];					
						store_trustee_belief_parameters[time_step][level][belief]=trustee_belief_parameters[level][belief];	
					}
				}						
			}
			//cout << calculationtime[sub_id] << endl;
			//ofs.write( reinterpret_cast<char*>( &calculationtime[sub_id] ),  sizeof calculationtime[sub_id] );			
		}
	}	
	ofs.close();

}
