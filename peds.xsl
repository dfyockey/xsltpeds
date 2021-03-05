<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:pat="http://www.wipo.int/standards/XMLSchema/ST96/Patent" xmlns:uscom="urn:us:gov:doc:uspto:common" xmlns:uspat="urn:us:gov:doc:uspto:patent" xmlns:com="http://www.wipo.int/standards/XMLSchema/ST96/Common" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:meta="myns:meta">

<!--
    peds.xsl - Patent Examination Data System XSLT Transform Stylesheet

    Copyright © 2020-2021 David Yockey

    This file is part of Xsltpeds.

    Xsltpeds is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xsltpeds is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Xsltpeds.  If not, see <https://www.gnu.org/licenses/>.
-->

<xsl:output method="html"/>

<meta:metadata>
	<xsltprocessor>Xsltpeds 1.0.0</xsltprocessor>
	<thisfile>peds.xsl 1.0.0</thisfile>
	<pedsschema>V8_0</pedsschema>
</meta:metadata>

<xsl:variable name="varMetadata" select="document('')/*/meta:metadata"/>

<!-- =============== -->
<!--  MAIN TEMPLATE  -->
<!-- =============== -->

<xsl:template match="/uspat:PatentBulkData">
	<html>
		
		<head>
		<meta name="generator">           <xsl:attribute name="content"><xsl:value-of select="$varMetadata/xsltprocessor"/></xsl:attribute>  </meta>
		<meta name="transformation-file"> <xsl:attribute name="content"><xsl:value-of select="$varMetadata/thisfile"/></xsl:attribute>   </meta>
		<meta name="uspto-peds-schema">   <xsl:attribute name="content"><xsl:value-of select="$varMetadata/pedsschema"/></xsl:attribute> </meta>

<xsl:text>

</xsl:text>

<!-- THE FOLLOWING LICENSE DOES NOT APPLY TO THIS STYLESHEET FILE! -->
<!-- IT APPLIES ONLY TO HTML FILES GENERATED USING THIS FILE!!!!!! -->
<xsl:comment>
  License : BSD-3-Clause

    Copyright © 2021 David Yockey

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
</xsl:comment>

<xsl:text>

			</xsl:text><script language="javascript">

				// Utility to align an element to the top of the viewport
				function alignClickedTitleToTop(e) {
					var t = document.getElementById("trailer");
					t.style.height = screen.height;
					t.style.display = "block";
					e.scrollIntoView(true);
					t.style.display = "none";
				}

				// Utility to show/hide an element
				function toggleElement(e) {
					if (e.style.display === "none") {
						e.style.display = "block";
					} else {
						e.style.display = "none";
					}
				}

				// Show/hide all applications' info, including title, except that having the clicked-on title
				function toggleOtherApplications(mouseevent) {
					var d, i;
					d = document.querySelectorAll(".application");
					for (i = 0; i &lt; d.length; i++) {
						if (d[i] !== mouseevent.target.parentElement)
							toggleElement(d[i]);
					}

					alignClickedTitleToTop(mouseevent.target);
				}

				// Show/hide applications' data blocks except Application Data
				function toggleDetails(mouseevent) {
					var d, i;
					d = document.querySelectorAll(".details");
					for (i = 0; i &lt; d.length; i++) {
						toggleElement(d[i]);
					}

					alignClickedTitleToTop(mouseevent.target.parentNode.parentNode.previousElementSibling);
				}

			</script>

			<style type="text/css">
				body {
					font-family:sans-serif;
				}
				
				.content {
					width:900px;
					margin:auto;
				}
				
				.doctitle {
					margin-bottom:0em;
				}
				
				hr {
					margin:1em 0 2.5em 0;
					border: 1px dashed blue;
				}
				
				table {
					border:solid black 1px;
					margin-bottom:1em;
					width:900px;
				}
				
					caption {
						text-align:left;
						font-style:italic;
					}
				
					td {
						border-bottom:solid #dddddd 1px;
						padding-left:1ex;
						padding-right:1ex;
						vertical-align:top;
					}
					
					.rj {
						text-align:right;
					}
					
					.intreg {
						text-decoration: line-through;
					}
					
					.listtbl th, .blocktbl th {
						text-align:left;
						padding-left:1ex;
						color:#FFFFFF;
						background-color:#999999;
						font-style:italic;
					}
					
					.listtbl th, .listtbl td, .blocktbl th {
						padding-top:1ex;
						padding-bottom:1ex;
					}

					.blocktbl td {
						line-height:1.4em;
					}

					.grayrow {
						background-color:#ececec;
					}

					.details {
						display:block;
					}

					#trailer {
						height:1000px;
						display:none;
					}
			</style>
		</head>
		
		<body>
			<div class="content">
				
				<xsl:for-each select="uspat:PatentData">
				  <div class="application">
					<xsl:apply-templates select="uspat:PatentCaseMetadata"/>												<!-- Application Data			-->
					<div class="details">
						<xsl:apply-templates select="uspat:ProsecutionHistoryDataBag"/>											<!-- Transaction History		-->
						<xsl:apply-templates select="uspat:PatentTermData/uspat:PatentTermAdjustmentData"/>						<!-- Patent Term Adjustment		-->
						<xsl:apply-templates select="uspat:PatentCaseMetadata/uspat:PartyBag/com:CorrespondenceAddress"/>		<!-- Correspondence Address		-->
						<xsl:apply-templates select="uspat:PatentCaseMetadata/uspat:PartyBag/uspat:RegisteredPractitionerBag"/>	<!-- Attorney/Agent Information -->
						<xsl:apply-templates select="uspat:PatentCaseMetadata/uspat:RelatedDocumentData"/>						<!-- Continuity Data			-->
						<xsl:apply-templates select="uspat:PatentCaseMetadata/uspat:PriorityClaimBag"/>							<!-- Foreign Priority			-->
						<xsl:apply-templates select="uspat:AssignmentDataBag"/>													<!-- Assignments				-->
				    </div>
				  </div>
				</xsl:for-each>
				
				<hr />
				<div id="trailer"></div>
			</div>
		</body>
		
	</html>
</xsl:template>

<!-- ================ -->
<!--  DATA TEMPLATES  -->
<!-- ================ -->

<!-- Application Data -->
<xsl:template match="uspat:PatentCaseMetadata">
	
	<xsl:variable name="first2file">
		<xsl:choose><xsl:when test="uspat:FirstInventorToFileIndicator = 'true'">Yes</xsl:when><xsl:otherwise>No</xsl:otherwise></xsl:choose>
	</xsl:variable>

	<xsl:variable name="pubnum">
		<xsl:choose><xsl:when test="uscom:ApplicationTypeCategory = 'PCT'">WIPO Publication Number:</xsl:when><xsl:otherwise>Earliest Publication No (PGPUB):</xsl:otherwise></xsl:choose>
	</xsl:variable>

	<xsl:variable name="pubdate">
		<xsl:choose><xsl:when test="uscom:ApplicationTypeCategory = 'PCT'">WIPO Publication Date:</xsl:when><xsl:otherwise>Earliest Publication Date:</xsl:otherwise></xsl:choose>
	</xsl:variable>

	<hr />
	<h2 class="doctitle" onclick="toggleOtherApplications(event)"><xsl:value-of select="pat:InventionTitle"/></h2>
	<table class="blocktbl">
		<!-- AFAIK, values for the International Reg No and Reg Pub Date in this table apparently may only appear in design patents -->
		<caption onclick="toggleDetails(event)"><h3>Application Data</h3></caption>
		<tr>
			<td class="rj" width="25%">Application Number:</td><td width="25%"><xsl:value-of select="uscom:ApplicationNumberText"/></td>
			<td class="rj" width="25%">Correspondence Address Customer Number:</td><td width="25%"><xsl:value-of select="uspat:PartyBag/com:CorrespondenceAddress/com:PartyIdentifier"/></td></tr>
		<tr>
			<td class="rj">Filing or 371 (c) Date:</td><td><xsl:value-of select="pat:FilingDate"/></td>
			<td class="rj">Status:</td><td><xsl:value-of select="uscom:ApplicationStatusCategory"/></td></tr>
		<tr>
			<td class="rj">Application Type:</td><td><xsl:value-of select="uscom:ApplicationTypeCategory"/></td>
			<td class="rj">Status Date:</td><td><xsl:value-of select="uscom:ApplicationStatusDate"/></td></tr>
		<tr>
			<td class="rj">Examiner Name:</td><td><xsl:for-each select="uspat:PartyBag/pat:ExaminerBag/*"><xsl:value-of select="com:Name/com:PersonName/com:PersonFullName"/><br /></xsl:for-each></td>
			<td class="rj">Location:</td><td><xsl:value-of select="uscom:OfficialFileLocationCategory"/></td></tr>
		<tr>
			<td class="rj">Group Art Unit:</td><td><xsl:value-of select="uscom:GroupArtUnitNumber"/></td>
			<td class="rj">Location Date:</td><td><xsl:value-of select="uscom:OfficialFileLocationDate"/></td></tr>
		<tr>
			<td class="rj">Confirmation Number:</td><td><xsl:value-of select="uspat:ApplicationConfirmationNumber"/></td>
			<td class="rj"><xsl:value-of select="$pubnum"/></td><td><xsl:value-of select="uspat:PatentPublicationIdentification/com:IPOfficeCode"/><xsl:value-of select="uspat:PatentPublicationIdentification/pat:PublicationNumber"/></td></tr>
		<tr>
			<td class="rj">Attorney Docket Number:</td><td><xsl:value-of select="com:ApplicantFileReference"/></td>
			<td class="rj"><xsl:value-of select="$pubdate"/></td><td><xsl:value-of select="uspat:PatentPublicationIdentification/com:PublicationDate"/></td></tr>
		<tr>
			<td class="rj">Class / Subclass:</td><td><xsl:value-of select="pat:PatentClassificationBag/pat:NationalClassification/pat:MainNationalClassification/pat:NationalClass"/>/<xsl:value-of select="pat:PatentClassificationBag/pat:NationalClassification/pat:MainNationalClassification/pat:NationalSubclass"/></td>
			<td class="rj">Patent Number:</td><td><xsl:value-of select="uspat:PatentGrantIdentification/pat:PatentNumber"/></td></tr>
		<tr>
			<td class="rj"></td><td></td>
			<td class="rj">Issue Date of Patent:</td><td><xsl:value-of select="uspat:PatentGrantIdentification/pat:GrantDate"/></td></tr>
		<tr class="grayrow">
			<td class="rj">Inventors:</td><td colspan="3"><div style="display:inline-block; float:left; margin-right:1em;"><xsl:for-each select="uspat:PartyBag/pat:InventorBag/pat:Inventor"><xsl:value-of select="com:PublicationContact/com:Name/com:PersonName/com:PersonStructuredName/com:FirstName"/>&#160;<xsl:if test="com:PublicationContact/com:Name/com:PersonName/com:PersonStructuredName/com:MiddleName != ''"><xsl:value-of select="com:PublicationContact/com:Name/com:PersonName/com:PersonStructuredName/com:MiddleName"/>&#160;</xsl:if><xsl:value-of select="com:PublicationContact/com:Name/com:PersonName/com:PersonStructuredName/com:LastName"/><br /></xsl:for-each></div><div style="display:inline-block; width=100%;"><xsl:for-each select="uspat:PartyBag/pat:InventorBag/pat:Inventor"><xsl:value-of select="com:PublicationContact/com:CityName"/><xsl:if test="com:PublicationContact/com:GeographicRegionName != ''">, <xsl:value-of select="com:PublicationContact/com:GeographicRegionName"/></xsl:if><xsl:if test="com:PublicationContact/com:CountryCode != ''">, <xsl:value-of select="com:PublicationContact/com:CountryCode"/></xsl:if><br /></xsl:for-each></div></td>
			</tr>
		<tr class="grayrow">
			<td class="rj">Applicants:</td><td colspan="3"><div style="display:inline-block; float:left; margin-right:1em;"><xsl:for-each select="uspat:PartyBag/pat:ApplicantBag/pat:Applicant"><xsl:value-of select="com:PublicationContact/com:Name/com:OrganizationName/com:OrganizationStandardName"/><br /></xsl:for-each></div><div style="display:inline-block; width=100%;"><xsl:for-each select="uspat:PartyBag/pat:ApplicantBag/pat:Applicant"><xsl:value-of select="com:PublicationContact/com:CityName"/><xsl:if test="com:PublicationContact/com:GeographicRegionName != ''">, <xsl:value-of select="com:PublicationContact/com:GeographicRegionName"/></xsl:if><xsl:if test="com:PublicationContact/com:CountryCode != ''">, <xsl:value-of select="com:PublicationContact/com:CountryCode"/></xsl:if><br /></xsl:for-each></div></td>
			</tr>
		<tr>
			<td class="rj">International Registration Number (Hague):</td><td><xsl:value-of select="com:HagueAgreementData/com:InternationalRegistrationNumber"/></td>
			<td class="rj">AIA (First Inventor to File):</td><td><xsl:value-of select="$first2file"/></td></tr>
		<tr>
			<td class="rj">International Registration Publication Date:</td><td><xsl:value-of select="com:HagueAgreementData/com:InternationalRegistrationPublicationDate"/></td>
			<td class="rj">Entity Status:</td><td><xsl:value-of select="uscom:BusinessEntityStatusCategory"/></td></tr>
	</table>

</xsl:template>

<!-- Transaction History -->
<xsl:template match="uspat:ProsecutionHistoryDataBag">
	<table class="listtbl">
		<caption><h3>Transaction History</h3></caption>
		<tr>
			<th width="20%">Date</th>
			<th width="20%">Code</th>
			<th width="*">Transaction Description</th>
		</tr>
		<xsl:for-each select="uspat:ProsecutionHistoryData">
			<tr>
				<td><xsl:value-of select="uspat:EventDate"/></td>
				<td><xsl:value-of select="uspat:EventCode"/></td>
				<td><xsl:value-of select="uspat:EventDescriptionText"/></td>
			</tr>
		</xsl:for-each>
	</table>
</xsl:template>

<!-- Patent Term Adjustment -->
<xsl:template match="uspat:PatentTermData/uspat:PatentTermAdjustmentData">
	  
	<table class="blocktbl">
		<caption><h3>Patent Term Adjustment</h3></caption>
		<tr>
			<td>Filing or 371(c) Date:</td><td><xsl:value-of select="/uspat:PatentBulkData/uspat:PatentData/uspat:PatentCaseMetadata/pat:FilingDate"/></td>
			<td>Overlapping Days Between {A and B} or {A and C}:</td><td><xsl:value-of select="uspat:OverlappingDayQuantity"/></td></tr>
		<tr>
			<td>Issue Date of Patent:</td><td><xsl:value-of select="/uspat:PatentBulkData/uspat:PatentData/uspat:PatentCaseMetadata/uspat:PatentGrantIdentification/pat:GrantDate"/></td>
			<td>Non-Overlapping USPTO Delays:</td><td><xsl:value-of select="uspat:NonOverlappingDayQuantity"/></td></tr>
		<tr>
			<td>A Delays:</td><td><xsl:value-of select="uspat:ADelayQuantity"/></td>
			<td>PTO Manual Adjustments:</td><td><xsl:value-of select="uspat:IPOfficeDayDelayQuantity"/></td></tr>
		<tr>
			<td>B Delays:</td><td><xsl:value-of select="uspat:BDelayQuantity"/></td>
			<td>Applicant Delays:</td><td><xsl:value-of select="uspat:ApplicantDayDelayQuantity"/></td></tr>
		<tr>
			<td>C Delays:</td><td><xsl:value-of select="uspat:CDelayQuantity"/></td>
			<td>Total PTA Adjustments:</td><td><xsl:value-of select="uspat:AdjustmentTotalQuantity"/></td></tr>
	</table>
	
	<table class="listtbl">
		<caption><h3>Patent Term Adjustment History</h3></caption>
		<tr>
			<th width="10%">Number</th>
			<th width="15%">Date</th>
			<th width="*">Contents Description</th>
			<th width="15%">PTO (Days)</th>
			<th width="15%">Appl (Days)</th>
			<th width="10%">Start</th>
		</tr>
		<xsl:for-each select="uspat:PatentTermAdjustmentHistoryDataBag/uspat:PatentTermAdjustmentHistoryData">
			<tr>
				<td><xsl:value-of select="uspat:EventSequenceNumber"/></td>
				<td><xsl:value-of select="uspat:EventDate"/></td>
				<td><xsl:value-of select="uspat:EventDescriptionText"/></td>
				<td><xsl:if test="uspat:IPOfficeDayDelayQuantity &gt; 0"><xsl:value-of select="uspat:IPOfficeDayDelayQuantity"/></xsl:if></td>
				<td><xsl:if test="uspat:ApplicantDayDelayQuantity &gt; 0"><xsl:value-of select="uspat:ApplicantDayDelayQuantity"/></xsl:if></td>
				<td><xsl:value-of select="uspat:OriginatingEventSequenceNumber"/></td>
			</tr>
		</xsl:for-each>
	</table>
	
</xsl:template>

<!-- Correspondence Address -->
<xsl:template match="uspat:PatentCaseMetadata/uspat:PartyBag/com:CorrespondenceAddress">
	<table class="blocktbl">
		<caption><h3>Correspondence Address</h3></caption>
		<tr><td>Name:</td><td><xsl:value-of select="com:Contact/com:Name/com:PersonName/com:PersonStructuredName/com:LastName"/></td></tr>
		<xsl:for-each select="com:Contact/com:PostalAddressBag/com:PostalAddress/com:PostalStructuredAddress">
			<xsl:variable name="cc">
				<xsl:if test="(com:CountryCode != 'US') and (com:CountryCode != 'null')"><xsl:value-of select="com:CountryCode"/>,</xsl:if>
			</xsl:variable>
			<tr><td>Address:</td><td><xsl:value-of select="com:AddressLineText"/>, <xsl:value-of select="com:CityName"/>, <xsl:value-of select="com:GeographicRegionName"/>, <xsl:value-of select="$cc"/><xsl:value-of select="com:PostalCode"/></td></tr>
		</xsl:for-each>
		<tr><td>Customer Number:</td><td><xsl:value-of select="com:PartyIdentifier"/></td></tr>
	</table>
</xsl:template>

<!-- Attorney/Agent Information -->
<xsl:template match="uspat:PatentCaseMetadata/uspat:PartyBag/uspat:RegisteredPractitionerBag">
	<table class="listtbl">
		<caption><h3>Attorney/Agent Information</h3></caption>
		<tr><th width="20%">Reg#</th><th width="40%">Name</th><th width="40%">Phone</th></tr>
		<xsl:for-each select="uspat:RegisteredPractitioner">
			<tr>
				<td><xsl:value-of select="pat:RegisteredPractitionerRegistrationNumber"/></td>
				<td><xsl:value-of select="com:Contact/com:Name"/><xsl:if test="@uscom:activeIndicator = 'false'">(not active)</xsl:if></td>
				<td><xsl:value-of select="com:Contact/com:PhoneNumberBag"/></td>
			</tr>
		</xsl:for-each>
	</table>
</xsl:template>

<!-- Continuity Data -->
<xsl:template match="uspat:PatentCaseMetadata/uspat:RelatedDocumentData">

	<table class="listtbl">
		<caption><h3>Parent Continuity Data</h3></caption>
		<tr>
			<th width="20%">Description</th>
			<th width="16%">Parent Number</th>
			<th width="16%">Parent Filing or 371(C) Date</th>
			<th width="16%">AIA(First Inventor to File)</th>
			<th width="16%">Parent Status</th>
			<th width="16%">Patent Number</th>
		</tr>

		<!-- Test to check for node non-existance - suggested by a comment responding to the answer at https://stackoverflow.com/a/767873/8100489 -->
		<!-- IF... -->
		<xsl:if test="not(uspat:ParentDocumentData/node())"><tr><td>No Parent Continuity Data Found.</td></tr></xsl:if>
		<!-- ELSE... -->
		<xsl:for-each select="uspat:ParentDocumentData">
			<tr>
				<td><xsl:value-of select="uscom:DescriptionText"/></td>
				<td><xsl:value-of select="com:ApplicationNumberText"/></td>
				<td><xsl:value-of select="pat:FilingDate"/></td>
				<td><xsl:choose><xsl:when test="uspat:AIAIndicator = 'true'">Yes</xsl:when><xsl:otherwise>No</xsl:otherwise></xsl:choose></td>
				<td><xsl:value-of select="pat:ParentDocumentStatusCode"/></td>
				<td><xsl:value-of select="pat:PatentNumber"/></td>
			</tr>
		</xsl:for-each>
		
	</table>

	<table class="listtbl">
		<caption><h3>Child Continuity Data</h3></caption>
		
		<!-- Test to check for node non-existance - suggested by a comment responding to the answer at https://stackoverflow.com/a/767873/8100489 -->
		<!-- IF... -->
		<xsl:if test="not(uspat:ChildDocumentData/node())"><tr><td>No Child Continuity Data Found.</td></tr></xsl:if>
		<!-- ELSE... -->
		<xsl:for-each select="uspat:ChildDocumentData">
			<tr><td><xsl:value-of select="com:ApplicationNumberText"/> filed on <xsl:value-of select="pat:FilingDate"/>&#160;<xsl:value-of select="uscom:DescriptionText"/></td></tr>
		</xsl:for-each>
		
	</table>

</xsl:template>

<!-- Foreign Priority tab -->
<xsl:template match="uspat:PatentCaseMetadata/uspat:PriorityClaimBag">
	<table class="listtbl">
		<caption><h3>Foreign Priority</h3></caption>
		<tr><th width="*">Country</th><th width="33%">Priority Application Number</th><th width="33%">Priority Filing Date</th></tr>
		<xsl:for-each select="uspat:PriorityClaim">
			<tr>
				<td><xsl:value-of select="uscom:IPOfficeName"/></td>
				<td><xsl:value-of select="com:ApplicationNumber/com:ApplicationNumberText"/></td>
				<td><xsl:value-of select="pat:FilingDate"/></td>
			</tr>
		</xsl:for-each>
	</table>
</xsl:template>

<!-- Assignments tab -->
<xsl:template match="uspat:AssignmentDataBag">
	<xsl:variable name="numassigns" select="@uspat:assignmentTotalQuantity"/>
	<xsl:for-each select="uspat:AssignmentData">
		<table class="blocktbl">
			<xsl:if test="position() = 1"><caption><h3>Patent Assignment Abstract of Title</h3></caption></xsl:if>
			<tr>
				<th colspan="4">Assignment: <xsl:value-of select="position()"/> of <xsl:value-of select="$numassigns"/></th></tr>
			<tr>
				<td width="20%" class="rj">Reel/Frame:</td>
				<td width="*"><xsl:value-of select="uspat:ReelNumber"/>/<xsl:value-of select="uspat:FrameNumber"/></td>
				<td width="20%" class="rj"></td>
				<td width="20%"></td></tr>
			<tr>
				<td class="rj">Pages</td>
				<td><xsl:value-of select="com:PageTotalQuantity"/></td>
				<td class="rj">Received date:</td>
				<td><xsl:value-of select="com:DocumentReceivedDate"/></td></tr>
			<tr>
				<td class="rj">Recorded date:</td>
				<td><xsl:value-of select="uscom:RecordedDate"/></td>
				<td class="rj">Mailed date:</td>
				<td><xsl:value-of select="com:MailDate"/></td></tr>
			<tr>
				<td class="rj">Conveyance:</td>
				<td><xsl:value-of select="uscom:ConveyanceText"/></td>
				<td class="rj"></td>
				<td></td></tr>
			<xsl:for-each select="uspat:AssignorBag/uspat:Assignor">
				<tr class="grayrow">
					<td class="rj"><xsl:if test="position() = 1">Assignor:</xsl:if></td>
					<td><xsl:value-of select="com:Contact"/></td>
					<td class="rj">Exec Date:</td>
					<td><xsl:value-of select="uscom:ExecutionDate"/></td>
				</tr></xsl:for-each>
			<xsl:for-each select="pat:AssigneeBag/pat:Assignee">
				<tr>
					<td class="rj"><xsl:if test="position() = 1">Assignee:</xsl:if></td>
					<td colspan="3">
						<xsl:value-of select="com:Contact/com:Name"/><br />
						<xsl:for-each select="com:Contact/com:PostalAddressBag/com:PostalAddress/com:PostalAddressText"><xsl:value-of select="."/><br />
						</xsl:for-each></td>
				</tr></xsl:for-each>
			<tr class="grayrow">
				<td class="rj">Correspondent:</td>
				<td colspan="3">
					<xsl:value-of select="com:CorrespondenceAddress/com:Contact/com:Name"/><br />
					<xsl:for-each select="com:CorrespondenceAddress/com:Contact/com:PostalAddressBag/com:PostalAddress/com:PostalAddressText"><xsl:value-of select="."/><br />
					</xsl:for-each></td>
				</tr>
		</table>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
